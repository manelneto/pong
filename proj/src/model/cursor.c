#include <lcom/lcf.h>

#include "cursor.h"

#include "../xpm/cursor.xpm"

Cursor *construct_cursor(int16_t x, int16_t y) {
  Cursor *cursor = (Cursor *) malloc(sizeof(Cursor));

  if (!cursor) {
    printf("%s: malloc() error\n", __func__);
    return NULL;
  }

  cursor->x = x;
  cursor->y = y;
  cursor->sprite = construct_sprite((xpm_map_t) cursor_xpm, 0x000000);

  if (!cursor->sprite) {
    printf("%s: construct_sprite(cursor_xpm) error\n", __func__);
    return NULL;
  }

  return cursor;
}

int move_cursor(Cursor *cursor, int16_t x, int16_t y, uint16_t x_max, uint16_t y_max) {
  if (!cursor) {
    printf("%s: cursor is NULL\n", __func__);
    return 1;
  }
  cursor->x = x;
  cursor->y = y;
  return 0;
}

void destroy_cursor(Cursor *cursor) {
  if (cursor)
    free(cursor);
}
