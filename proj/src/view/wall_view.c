#include <lcom/lcf.h>

#include "wall_view.h"

#include "../controller/video.h"

int draw_wall(Wall *wall) {
  if (!wall) {
    printf("%s: wall is NULL\n", __func__);
    return 1;
  }

  if (video_draw_rectangle(wall->x, wall->y, wall->w, wall->h, 0xffffff)) {
    printf("%s: video_draw_rectangle(wall->x; %d, wall->y: %d, wall->w: %d, wall->h: %d, 0xffffff) error\n", __func__, wall->x, wall->y, wall->w, wall->h, 0xffffff);
    return 1;
  }

  return 0;
}
