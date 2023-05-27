#include <lcom/lcf.h>

#include "button_view.h"

#include "../controller/video.h"

int draw_button(Button *button) {
  if (!button) {
    printf("%s: button is NULL\n", __func__);
    return 1;
  }

  if (video_draw_rectangle(button->x, button->y, button->w, button->h, 0xffffff)) {
    printf("%s: video_draw_rectangle(button->x: %d, button->y: %d, button->w: %d, button->h: %d, 0x%x) error\n", __func__, button->x, button->y, button->w, button->h, 0xffffff);
    return 1;
  }

  return 0;
}
