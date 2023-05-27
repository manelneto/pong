#include <lcom/lcf.h>

#include "menu.h"
#include "levels.h"
#include "game.h"
#include "model.h"

#include "../view/view.h"

#include "../controller/keyboard.h"
#include "../controller/mouse.h"
#include "../controller/video.h"

State state = MENU;

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

void timer_interrupt_handler() {
  timer_int_handler();
  swap_buffers();
  switch (state) {
    case MENU:
      break;
    case GAME:
      timer_game_handler();
      if (check_game_over()) {
        state = MENU;
        end_game();
      }
      draw_frame();
      break;
    case LEVELS:
      break;
    case END:
      break;
    default:
      break;
  }
}

void keyboard_interrupt_handler() {
  kbc_ih();
  if (code.size > 0) { // code complete
    switch (state) {
      case MENU:
        if (code.bytes[0] == KBD_ESC_BREAKCODE) {
          state = END;
          break;
        }
        keyboard_menu_handler();
        if (check_play() && !code.makecode) {
          state = LEVELS;
          start_levels(vmi_p.XResolution, vmi_p.YResolution);
        }
        else if (check_quit() && !code.makecode)
          state = END;
        break;
      case GAME:
        keyboard_game_handler();
        break;
      case LEVELS:
        keyboard_levels_handler();
      case END:
        break;
      default:
        break;
    }
    keyboard_restore();
    draw_frame();
  }
}

void mouse_interrupt_handler() {
  mouse_ih();
  if (packet_index == 3) { // packet complete
    switch (state) {
      case MENU:
        mouse_menu_handler();
        if (check_play() && mouse_packet.lb) {
          state = LEVELS;
          start_levels(vmi_p.XResolution, vmi_p.YResolution);
        }
        else if (check_quit() && mouse_packet.lb)
          state = END;
        break;
      case GAME:
        mouse_game_handler();
        break;
      case LEVELS:
        mouse_levels_handler();
        if (check_easy() && mouse_packet.lb) {
          end_levels();
          state = GAME;
          start_game(vmi_p.XResolution, vmi_p.YResolution);
        }
        else if (check_medium() && mouse_packet.lb) {
          end_levels();
          state = GAME;
          start_game(vmi_p.XResolution, vmi_p.YResolution);
        }
        else if (check_hard() && mouse_packet.lb) {
          end_levels();
          state = GAME;
          start_game(vmi_p.XResolution, vmi_p.YResolution);
        }
        break;
      case END:
        break;
      default:
        break;
    } 
    mouse_restore();
    draw_frame();
  }
}

void end_pong() {
  end_game();
  end_levels();
  end_menu();
}
