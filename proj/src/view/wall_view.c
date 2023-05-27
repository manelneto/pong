#include <lcom/lcf.h>

#include "wall_view.h"

#include "../controller/video.h"

int draw_wall(Wall *wall) {
  if (!wall) {
    printf("%s: wall is NULL\n", __func__);
    return 1;
  }

  for (uint16_t i = 0; i < wall->l; i++)
    if (video_draw_pixel(wall->x, wall->y + i, 0xffffff)) {
      printf("%s: video_draw_pixel(wall->x: %d, wall->y + i: %d, color: 0x%x) error\n", __func__, wall->x, wall->y + i, 0xffffff);
      return 1;
    }

  return 0;
}
