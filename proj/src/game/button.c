#include <lcom/lcf.h>

#include "button.h"

#include "../drivers/video_gr.h"

Button *construct_button(uint16_t x, uint16_t y, uint8_t w, uint8_t h) {
  Button *button = (Button *) malloc(sizeof(Button));

  if (!button) {
    printf("%s: malloc() error\n", __func__);
    return NULL;
  }

  button->x = x;
  button->y = y;
  button->w = w;
  button->h = h;
  button->selected = false;

  return button;
}

int draw_button(Button *button) {
  if (!button) {
    printf("%s: button is NULL\n", __func__);
    return 1;
  }

  if (vg_draw_rectangle(button->x, button->y, button->w, button->h, 0xffffff)) {
    printf("%s: vg_draw_rectangle(button->x: %d, button->y: %d, button->w: %d, button->h: %d, 0x%x) error\n", __func__, button->x, button->y, button->w, button->h, 0xffffff);
    return 1;
  }

  return 0;
}

int update_button(Button *button, uint16_t x, uint16_t y) {
  if (!button) {
    printf("%s: button is NULL\n", __func__);
    return 1;
  }

  if (x >= button->x && (x <= button->x + button->w) && y >= button->y && (y <= button->y + button->h))
    button->selected = true;
  else
    button->selected = false;

  return 0;
}

void destroy_button(Button *button) {
  if (button)
    free(button);
}
