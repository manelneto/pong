#include <lcom/lcf.h>

#include "view.h"

#include "model/model.h"

#include "menu_view.h"
#include "game_view.h"

#include "../controller/video.h"

extern GameState state;

int draw_frame() {
  if (video_clean(0, 0, 800, 600)) {
    printf("%s: vg_clean(0, 0, 800, 600) error\n", __func__);
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
