#include <lcom/lcf.h>

#include "menu.h"

#include "button.h"
#include "cursor.h"

#include "../controller/keyboard.h"
#include "../controller/mouse.h"

extern scancode code;
extern struct packet mouse_packet;

Button *play = NULL;
Button *quit = NULL;
Cursor *cursor = NULL;

static uint16_t x_max;
static uint16_t y_max;

static uint16_t x;
static uint16_t y;

int start_menu(uint16_t xResolution, uint16_t yResolution) {
  play = construct_button(xResolution/3, yResolution/5, xResolution/3, yResolution/5);
  if (!play) {
    printf("%s: construct_button(%d, %d, %d, %d) error\n", __func__, xResolution/3, yResolution/5, xResolution/3, yResolution/5);
    return 1;
  }

  quit = construct_button(xResolution/3, 3 * yResolution/5, xResolution/3, yResolution/5);
  if (!quit) {
    printf("%s: construct_button(%d, %d, %d, %d) error\n", __func__, xResolution/3, 3 * yResolution/5, xResolution/3, yResolution/5);
    return 1;
  }

  cursor = construct_cursor(xResolution/2, yResolution/2);
  if (!cursor) {
    printf("%s: construct_cursor(%d, %d) error\n", __func__, xResolution/2, yResolution/2);
    return 1;
  }

  x_max = xResolution;
  y_max = yResolution;

  x = cursor->x;
  y = cursor->y;

  return 0;
}

void keyboard_menu_state_handler() {
  if ((code.size == 2 && code.bytes[0] == KBD_ARROW_UP_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_W_MAKECODE))
    play->selected = true;
  if ((code.size == 2 && code.bytes[0] == KBD_ARROW_DOWN_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_S_MAKECODE))
    quit->selected = true;
}

void mouse_menu_state_handler() {
  x += mouse_packet.delta_x;
  y -= mouse_packet.delta_y;
  move_cursor(cursor, x, y, x_max, y_max);
  if (mouse_packet.lb) {
    check_button(play, cursor->x, cursor->y);
    check_button(quit, cursor->x, cursor->y);
  } else {
    play->selected = false;
    quit->selected = false;
  }
}

bool check_play() {
  return play->selected;
}

bool check_quit() {
  return quit->selected;
}

void end_menu() {
  destroy_button(play);
  destroy_button(quit);
  destroy_cursor(cursor);
}
