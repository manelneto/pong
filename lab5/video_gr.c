#include <lcom/lcf.h>

#include <lcom/video_gr.h>

#include "vbe_constants.h"

static void *video_mem;          /* Process (virtual) address to which VRAM is mapped */

static unsigned h_res;           /* Horizontal resolution in pixels */
static unsigned v_res;           /* Vertical resolution in pixels */
static unsigned bits_per_pixel;  /* Number of VRAM bits per pixel */
static unsigned bytes_per_pixel; /* Number of VRAM bytes per pixel*/

vbe_mode_info_t vmi_p;

void* (vg_init)(uint16_t mode) {
  /* 1. Initialize static global variables */
  if (vbe_get_mode_info(mode, &vmi_p)) {
    printf("%s: vbe_get_mode_info error\n", __func__);
    return NULL;
  }
  h_res = vmi_p.XResolution;
  v_res = vmi_p.YResolution;
  bits_per_pixel = vmi_p.BitsPerPixel;
  bytes_per_pixel = (bits_per_pixel + 7)/8;

  /* 2. Map VRAM to the process' address space */
  struct minix_mem_range mr;
  unsigned int vram_base = vmi_p.PhysBasePtr;               /* VRAM's physical address */
  unsigned int vram_size = h_res * v_res * bytes_per_pixel; /* VRAM's size */
  
  /* Allow memory mapping */
  mr.mr_base = (phys_bytes) vram_base;
  mr.mr_limit = mr.mr_base + vram_size;
  if (sys_privctl(SELF, SYS_PRIV_ADD_MEM, &mr)) {
    printf("%s: sys_privctl error\n", __func__);
    return NULL;
  }

  /* Map memory */
  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
  if (video_mem == MAP_FAILED) {
    printf("%s: vm_map_phys error\n", __func__);
    return NULL;
  }

  /* 3. Set the desired graphics mode using a linear frame buffer */
  reg86_t r;

  /* Specifiy the appropriate register values */
  memset(&r, 0, sizeof(r));          /* zero the structure */
  r.intno = VBE_INTNO;               /* BIOS video services */
  r.ah = VBE_REG_AH;
  r.al = VBE_SET_MODE;
  r.bx = mode | VBE_SET_LINEAR_MODE;

  /* Make the BIOS call */
  if (sys_int86(&r)) {
    printf("%s: sys_int86 error\n", __func__);
    return NULL;
  }

  return video_mem;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  if (x < 0 || x >= h_res || y < 0 || y >= v_res) {
    printf("%s: pixel (%d, %d) error\n", __func__, x, y);
    return 0;
  }

  uint8_t *byte = video_mem;
  byte += (x + y * h_res) * bytes_per_pixel;
  
  for (unsigned i = 0; i < bytes_per_pixel; i++, byte++, color >>= 8)
    *byte = (uint8_t) color;
  
  return 0;
}

int (vg_draw_hline)(uint16_t x, uint16_t y, uint16_t len, uint32_t color) {
  for (uint16_t i = 0; i < len; i++) {
    if (vg_draw_pixel(x + i, y, color)) {
      printf("%s: vg_draw_pixel error\n", __func__);
      return 1;
    }
  }
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (uint16_t i = 0; i < height; i++) {
    if (vg_draw_hline(x, y + i, width, color)) {
      printf("%s: vg_draw_hline error\n", __func__);
      return 1;
    }
  }
  return 0;
} 
