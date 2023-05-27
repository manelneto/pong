#include <lcom/lcf.h>

#include "menu.h"

#include "button.h"
#include "cursor.h"

#include "../controller/keyboard.h"
#include "../controller/mouse.h"

#include "../xpm/button_play.xpm"
#include "../xpm/button_play_selected.xpm"
#include "../xpm/button_quit.xpm"
#include "../xpm/button_quit_selected.xpm"

extern scancode code;
extern struct packet mouse_packet;

Button *play = NULL;
Button *quit = NULL;
Cursor *cursor = NULL;

static uint16_t x_max;
static uint16_t y_max;

static int16_t x;
static int16_t y;

int start_menu(uint16_t xResolution, uint16_t yResolution) {
  play = construct_button(xResolution/3, yResolution/5, xResolution/3, yResolution/5, button_play_xpm, button_play_selected_xpm);
  if (!play) {
    printf("%s: construct_button(%d, %d, %d, %d) error\n", __func__, xResolution/3, yResolution/5, xResolution/3, yResolution/5);
    return 1;
  }

  quit = construct_button(xResolution/3, 3 * yResolution/5, xResolution/3, yResolution/5, button_quit_xpm, button_quit_selected_xpm);
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

void keyboard_menu_handler() {
  if ((code.size == 2 && code.bytes[1] == KBD_ARROW_UP_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_W_MAKECODE))
    play->selected = true;
  if ((code.size == 2 && code.bytes[1] == KBD_ARROW_DOWN_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_S_MAKECODE))
    quit->selected = true;
}

void mouse_menu_handler() {
  x += mouse_packet.delta_x;
  if (x < 0) x = 0;
  else if (x + cursor->sprite->width >= x_max) x = x_max - cursor->sprite->width - 1;

  y -= mouse_packet.delta_y;
  if (y < 0) y = 0;
  else if (y + cursor->sprite->height >= y_max) y = y_max - cursor->sprite->height - 1;

  move_cursor(cursor, x, y, x_max, y_max);

  check_button(play, cursor->x, cursor->y);
  check_button(quit, cursor->x, cursor->y);
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
