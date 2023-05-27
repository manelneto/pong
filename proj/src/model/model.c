#include <lcom/lcf.h>

#include "game.h"
#include "menu.h"
#include "model.h"

#include "../view/view.h"

#include "../controller/keyboard.h"
#include "../controller/mouse.h"
#include "../controller/video.h"

SystemState systemState = RUNNING;
GameState state = MENU;

extern scancode code;
extern struct packet mouse_packet;
extern uint8_t packet_index;
extern vbe_mode_info_t vmi_p;

int start_pong() {
  if (start_menu(vmi_p.XResolution, vmi_p.YResolution)) {
    printf("%s: start_menu(vmi_p.XResolution: %d, vmi_p.YResolution: %d) error\n", __func__, vmi_p.XResolution, vmi_p.YResolution);
    return 1;
  }

  return 0;
}

void timer_state_handler() {
  timer_int_handler();
  if (state == GAME) {
    timer_game_state_handler();
    draw_frame();
    if (check_game_over()) {
      state = MENU;
      end_game();
    }
  }
  swap_buffers();
}

void keyboard_state_handler() {
  kbc_ih();
  if (code.size > 0) { // code complete
    if (code.bytes[0] == KBD_ESC_BREAKCODE)
      systemState = EXIT;
    else if (state == MENU)
      keyboard_menu_state_handler();
    else if (state == GAME)
      keyboard_game_state_handler();
    keyboard_restore();
  }
  draw_frame();
}

void mouse_state_handler() {
  mouse_ih();
  if (packet_index == 3) { // packet complete
    if (state == MENU) {
      mouse_menu_state_handler();
      if (check_play()) {
        state = GAME;
        start_game(vmi_p.XResolution, vmi_p.YResolution);
      } else if (check_quit()) {
        systemState = EXIT;
      }
    }
    else if (state == GAME)
      mouse_game_state_handler();
    mouse_restore();
    draw_frame();
  }
}

void end_pong() {
  end_menu();
  end_game();
}
