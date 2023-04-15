#include <lcom/lcf.h>

#include <lcom/video_gr.h>

#include "vbe_constants.h"

static char *video_mem;         /* Process (virtual) address to which VRAM is mapped */

static unsigned h_res;          /* Horizontal resolution in pixels */
static unsigned v_res;          /* Vertical resolution in pixels */
static unsigned bits_per_pixel; /* Number of VRAM bits per pixel */

void* (vg_init)(uint16_t mode) {
  /* 1. Initialize static global variables */
  vbe_mode_info_t vmi_p;
  if (vbe_get_mode_info(mode, &vmi_p)) {
    printf("%s: vbe_get_mode_info error\n", __func__);
    return NULL;
  }
  h_res = vmi_p.XResolution;
  v_res = vmi_p.YResolution;
  bits_per_pixel = vmi_p.BitsPerPixel;

  /* 2. Map VRAM to the process' address space */
  struct minix_mem_range mr;
  unsigned int vram_base = vmi_p.PhysBasePtr;                /* VRAM's physical address */
  unsigned int vram_size = h_res * v_res * bits_per_pixel/8; /* VRAM's size */
  
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
