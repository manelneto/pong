#include <lcom/lcf.h>

#include "view.h"

#include "model/model.h"

#include "menu_view.h"
#include "game_view.h"

#include "../controller/video.h"

#define BACKGROUND 0xADD8E6

extern State state;

int draw_frame() {
  if (video_draw_background(BACKGROUND)) {
    printf("%s: video_draw_background(BACKGROUND: %d) error\n", __func__, BACKGROUND);
    return 1;
  }

  if (state == MENU && draw_menu()) {
    printf("%s: draw_menu() error\n", __func__);
    return 1;
  }
  else if (state == GAME && draw_game()) {
    printf("%s: draw_game() error\n", __func__);
    return 1;
  }

  return 0;
}
