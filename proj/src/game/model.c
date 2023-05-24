#include <lcom/lcf.h>

#include "model.h"

#include "menu.h"
#include "game.h"

extern vbe_mode_info_t vmi_p;
State state = MENU;

int menu_to_game() {
  if (state != MENU) {
    printf("%s: menu_to_game() called when state != MENU\n", __func__);
    return 1;
  }

  menu_end();
  if (game_start(vmi_p.XResolution, vmi_p.YResolution)) {
    printf("%s: game_start(vmi_p.XResolution: %d, vmi_p.YResolution: %d) error\n", __func__, vmi_p.XResolution, vmi_p.YResolution);
    return 1;
  }
  state = GAME;
  return 0;
}

int game_to_menu() {
  if (state != GAME) {
    printf("%s: game_to_menu() called when state != GAME\n", __func__);
    return 1;
  }

  game_end();
  if (menu_start(vmi_p.XResolution, vmi_p.YResolution)) {
    printf("%s: menu_start(vmi_p.XResolution: %d, vmi_p.YResolution: %d) error\n", __func__, vmi_p.XResolution, vmi_p.YResolution);
    return 1;
  }
  state = MENU;
  return 0;
}
