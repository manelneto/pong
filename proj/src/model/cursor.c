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
  cursor->sprite = construct_sprite((xpm_map_t) cursor_xpm);

  if (!cursor->sprite) {
    printf("%s: construct_sprite(cursor_xpm) error\n", __func__);
    return NULL;
  }

  return cursor;
}


int move_cursor(Cursor *cursor, uint16_t x, uint16_t y, uint16_t x_max, uint16_t y_max) {
  if (!cursor) {
    printf("%s: cursor is NULL\n", __func__);
    return 1;
  }

  cursor->x = x;
  cursor->y = y;

  if (cursor->x < 0) cursor->x = 0;
  else if (cursor->x >= x_max) cursor->x = x_max - 1;

  if (cursor->y < 0) cursor->y = 0;
  else if (cursor->y >= y_max) cursor->y = y_max - 1;

  return 0;
}

void destroy_cursor(Cursor *cursor) {
  if (cursor)
    free(cursor);
}
