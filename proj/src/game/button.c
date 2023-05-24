#include <lcom/lcf.h>

#include "button.h"

#include "../drivers/video_gr.h"

Button *construct_button(int16_t x, int16_t y, uint8_t w, uint8_t h) {
  Button *button = (Button *) malloc(sizeof(Button));

  if (!button) {
    printf("%s: malloc() error\n", __func__);
    return NULL;
  }

  button->x = x;
  button->y = y;
  button->w = w;
  button->h = h;

  return button;
}

int draw_button(Button *button) {
  printf("button: (%d, %d, %d, %d)\n", button->x, button->y, button->w, button->h);
  vg_draw_rectangle(button->x, button->y, button->w, button->h, 0xffffff);

  /*for (uint16_t i = 0; i < button->h; i++)
    for (uint16_t j = 0; j < button->w; j++)
      if (vg_draw_pixel(button->x + j, button->y + i, 0xffffff)) {
        printf("%s: vg_draw_pixel(button->x: %d, button->y: %d, color: 0x%x) error\n", __func__, button->x, button->y, 0xffffff);
        return 1;
      }*/

  return 0;
}

void destroy_button(Button *button) {
  if (button)
    free(button);
}
