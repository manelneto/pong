#include <lcom/lcf.h>

#include "wall.h"

#include "../drivers/video_gr.h"

Wall* construct_wall(int16_t x, int16_t yi, int16_t yf) {
    Wall* wall = (Wall*) malloc(sizeof(Wall));

    if (!wall) {
        printf("%s: malloc() error\n", __func__);
        return NULL;
    }

    wall->x = x;
    wall->yi = yi;
    wall->yf = yf;

    return wall;
}

int draw_wall(Wall *wall) {
  for (int16_t y = wall->yi; y < wall->yf; y++)
    if (vg_draw_pixel(wall->x, y, 0xffffff)) {
      printf("%s: vg_draw_pixel(wall->x: %d, y: %d, color: 0x%x) error\n", __func__, wall->x, y, 0xffffff);
      return 1;
    }

  return 0;
}

void update_wall(Wall *ball) {
}

void destroy_wall(Wall *wall) {
    if (wall)
        free(wall);
}
