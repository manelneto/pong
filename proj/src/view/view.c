#include <lcom/lcf.h>

#include "view.h"

#include "model/model.h"

#include "menu_view.h"
#include "game_view.h"

#include "../controller/video.h"

extern State state;

int draw_frame() {
  if (video_draw_background(0xADD8E6)) {
    printf("%s: video_draw_background(0xADD8E6) error\n", __func__);
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
