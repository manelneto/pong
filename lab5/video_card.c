#include <lcom/lcf.h>
#include "video_card.h"

#include "vbe_constants.h"

uint32_t (vc_normalize_color)(uint32_t color) {
  if (vmi_p.BitsPerPixel == 32)
    return color;
  return color & (BIT(vmi_p.BitsPerPixel) - 1);
}

rgb_8_8_8_t (vc_get_colors)(uint32_t color) {
  uint8_t r = color >> vmi_p.RedFieldPosition % BIT(vmi_p.RedMaskSize);
  uint8_t g = color >> vmi_p.GreenFieldPosition % BIT(vmi_p.GreenMaskSize);
  uint8_t b = color >> vmi_p.BlueFieldPosition % BIT(vmi_p.BlueMaskSize);
  rgb_8_8_8_t colors = {r, g, b};
  return colors;
}

uint32_t (vc_get_color)(rgb_8_8_8_t colors) {
  uint32_t color = (colors.red << vmi_p.RedFieldPosition) | (colors.green << vmi_p.GreenFieldPosition) | (colors.blue << vmi_p.BlueFieldPosition);
  return color;
}

int (vc_draw_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  uint16_t width = vmi_p.XResolution/no_rectangles;
  uint16_t height = vmi_p.YResolution/no_rectangles;
  uint32_t color;
  rgb_8_8_8_t first_colors = vc_get_colors(first);

  for (uint8_t row = 0; row < no_rectangles; row++)
    for (uint8_t col = 0; col < no_rectangles; col++) {
      if (mode == VBE_INDEXED_COLOR_MODE)
        color = (first + (row * no_rectangles + col) * step) % (1 << vmi_p.BitsPerPixel);
      else {
        uint8_t r = (first_colors.red + col * step) % (1 << vmi_p.RedMaskSize);
        uint8_t g = (first_colors.green + row * step) % (1 << vmi_p.GreenMaskSize);
        uint8_t b = (first_colors.blue + (col + row) * step) % (1 << vmi_p.BlueMaskSize);
        rgb_8_8_8_t colors = {r, g, b};
        color = vc_get_color(colors);
      }
      if (vg_draw_rectangle(col * width, row * height, width, height, color)) {
        printf("%s: vg_draw_rectangle error\n", __func__);
        return 1;
      }
    }
  
  return 0;
}

int (vc_draw_pixmap)(uint16_t x, uint16_t y, xpm_image_t *image) {
  for (uint16_t row = 0; row < image->height; row++)
    for (uint16_t col = 0; col < image->width; col++)
      if (vg_draw_pixel(x + col, y + row, *(image->bytes + col + row * image->width))) {
        printf("%s: vg_draw_pixel error\n", __func__);
        return 1;
      }
  return 0;
}

int (vc_clean)(uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf) {
  for (uint16_t y = yi; y < yf; y++)
    for (uint16_t x = xi; x < xf; x++)
      if (vg_draw_pixel(x, y, 0)) {
        printf("%s: vg_draw_pixel error\n", __func__);
        return 1;
      }
  return 0;
}
