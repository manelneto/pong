#include <lcom/lcf.h>

#include "video_gr.h"

#include "VBE.h"

static void *video_mem;          /* Process (virtual) address to which VRAM is mapped */

static unsigned h_res;           /* Horizontal resolution in pixels */
static unsigned v_res;           /* Vertical resolution in pixels */
static unsigned bits_per_pixel;  /* Number of VRAM bits per pixel */
static unsigned bytes_per_pixel; /* Number of VRAM bytes per pixel*/

vbe_mode_info_t vmi_p;

void* (vg_init)(uint16_t mode) {
  /* 1. Initialize static global variables */
  if (vbe_get_mode_info(mode, &vmi_p)) {
    printf("%s: vbe_get_mode_info(mode: 0x%x, vmi_p) error\n", __func__, mode);
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
    printf("%s: sys_privctl(SELF, SYS_PRIV_ADD_MEM, mr) error\n", __func__);
    return NULL;
  }

  /* Map memory */
  video_mem = vm_map_phys(SELF, (void *)mr.mr_base, vram_size);
  if (video_mem == MAP_FAILED) {
    printf("%s: vm_map_phys(SELF, mr.mr_base, vram_size) error\n", __func__);
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
    printf("%s: sys_int86(r) error\n", __func__);
    return NULL;
  }

  return video_mem;
}

rgb_8_8_8_t (vg_get_colors)(uint32_t color) {
  uint8_t r = color >> vmi_p.RedFieldPosition % BIT(vmi_p.RedMaskSize);
  uint8_t g = color >> vmi_p.GreenFieldPosition % BIT(vmi_p.GreenMaskSize);
  uint8_t b = color >> vmi_p.BlueFieldPosition % BIT(vmi_p.BlueMaskSize);
  rgb_8_8_8_t colors = {r, g, b};
  return colors;
}

uint32_t (vg_get_color)(rgb_8_8_8_t colors) {
  uint32_t color = (colors.red << vmi_p.RedFieldPosition) | (colors.green << vmi_p.GreenFieldPosition) | (colors.blue << vmi_p.BlueFieldPosition);
  return color;
}

int (vg_draw_pixel)(uint16_t x, uint16_t y, uint32_t color) {
  if (x < 0 || x >= h_res || y < 0 || y >= v_res) {
    printf("%s: pixel (%d, %d) error\n", __func__, x, y);
    return 1;
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
      printf("%s: vg_draw_pixel(x + i: %d, y: %d, color: %d) error\n", __func__, x + i, y, color);
      return 1;
    }
  }
  return 0;
}

int (vg_draw_rectangle)(uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  for (uint16_t i = 0; i < height; i++) {
    if (vg_draw_hline(x, y + i, width, color)) {
      printf("%s: vg_draw_hline(x: %d, y + i: %d, width: %d, color: %d) error\n", __func__, x, y + i, width, color);
      return 1;
    }
  }
  return 0;
} 

int (vg_draw_pixmap)(uint16_t x, uint16_t y, xpm_image_t *image) {
  for (uint16_t row = 0; row < image->height; row++)
    for (uint16_t col = 0; col < image->width; col++)
      if (vg_draw_pixel(x + col, y + row, *(image->bytes + col + row * image->width))) {
        printf("%s: vg_draw_pixel(x + col: %d, y + row: %d, *(image->bytes + col + row * image->width): %d) error\n", __func__, x + col, y + row, *(image->bytes + col + row * image->width));
        return 1;
      }
  return 0;
}

int (vg_clean)(uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf) {
  for (uint16_t y = yi; y < yf; y++)
    for (uint16_t x = xi; x < xf; x++)
      if (vg_draw_pixel(x, y, 0)) {
        printf("%s: vg_draw_pixel(x: %d, y: %d, 0) error\n", __func__, x, y);
        return 1;
      }
  return 0;
}
