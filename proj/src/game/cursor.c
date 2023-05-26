#include <lcom/lcf.h>

#include "cursor.h"

#include "../drivers/video_gr.h"

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

int draw_cursor(Cursor *cursor) {
  if (!cursor) {
    printf("%s: cursor is NULL\n", __func__);
    return 1;
  }

  if (draw_sprite(cursor->sprite, cursor->x, cursor->y)) {
    printf("%s: draw_sprite(cursor->sprite, cursor->x: %d, cursor->y: %d) error\n", __func__, cursor->x, cursor->y);
    return 1;
  }

  return 0;
}

int move_cursor(Cursor *cursor, int16_t x, int16_t y) {
  if (!cursor) {
    printf("%s: cursor is NULL\n", __func__);
    return 1;
  }

  cursor->x = x;
  cursor->y = y;

  if (cursor->x < 0) cursor->x = 0;
  else if (cursor->x >= vmi_p.XResolution) cursor->x = vmi_p.XResolution - 1;

  if (cursor->y < 0) cursor->y = 0;
  else if (cursor->y >= vmi_p.YResolution) cursor->y = vmi_p.YResolution - 1;

  return 0;
}

void destroy_cursor(Cursor *cursor) {
  if (cursor)
    free(cursor);
}
