#include <lcom/lcf.h>

#include "cursor.h"

#include "../drivers/video_gr.h"

Cursor *construct_cursor(int16_t x, int16_t y) {
  Cursor *cursor = (Cursor *) malloc(sizeof(Cursor));

  if (!cursor) {
    printf("%s: malloc() error\n", __func__);
    return NULL;
  }

  cursor->x = x;
  cursor->y = y;

  return cursor;
}

int draw_cursor(Cursor *cursor) {
  if (!cursor) {
    printf("%s: cursor is NULL\n", __func__);
    return 1;
  }

  if (vg_draw_pixel(cursor->x, cursor->y, 0x123456)) {
    printf("%s: vg_draw_pixel(cursor->x: %d, cursor->y: %d, color: 0x%x) error\n", __func__, cursor->x, cursor->y, 0x123456);
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
