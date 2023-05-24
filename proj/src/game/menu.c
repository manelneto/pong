#include <lcom/lcf.h>

#include "menu.h"

#include "button.h"
#include "cursor.h"

#include "states.h"

static Button *play = NULL;
static Button *quit = NULL;
static Cursor *cursor = NULL;

extern State state;

int menu_start(uint16_t xResolution, uint16_t yResolution) {
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

  return 0;
}

int menu_draw() {
  if (draw_button(play)) {
    printf("%s: draw_button(play) error\n", __func__);
    return 1;
  }

  if (draw_button(quit)) {
    printf("%s: draw_button(quit) error\n", __func__);
    return 1;
  }

  return 0;
}

int menu_draw_cursor() {
  if (draw_cursor(cursor)) {
    printf("%s: draw_cursor(cursor) error\n", __func__);
    return 1;
  }

  return 0;
}

void menu_timer_ih() {
  // empty
}

void menu_keyboard_ih(MenuKey key) {
  // useless
  if (key == PLAY)
    play->selected = true;
  else if (key == QUIT)
    quit->selected = true;
  else if (key == ENTER) {
    if (play->selected) menu_to_game();
    if (quit->selected) state = EXIT;
  }
}

void menu_mouse_ih(int16_t x, int16_t y, bool lb) {
  move_cursor(cursor, x, y);
  if (lb) {
    update_button(play, x, y);
    update_button(quit, x, y);
    if (play->selected) menu_to_game();
    if (quit->selected) state = EXIT;
  }
}

void menu_end() {
  destroy_button(play);
  destroy_button(quit);
  destroy_cursor(cursor);
}
