#include <lcom/lcf.h>

#include "wall.h"

#include "../drivers/video_gr.h"

Wall *construct_wall(int16_t x, int16_t y, uint16_t l) {
  Wall *wall = (Wall *) malloc(sizeof(Wall));

  if (!wall) {
    printf("%s: malloc() error\n", __func__);
    return NULL;
  }

  wall->x = x;
  wall->y = y;
  wall->l = l;

  return wall;
}

int draw_wall(Wall *wall) {
  for (int16_t i = 0; i < wall->l; i++)
    if (vg_draw_pixel(wall->x, wall->y + i, 0xffffff)) {
      printf("%s: vg_draw_pixel(wall->x: %d, wall->y + i: %d, color: 0x%x) error\n", __func__, wall->x, wall->y + i, 0xffffff);
      return 1;
    }

  return 0;
}

void move_wall(Wall *wall, Direction direction) {
  if (direction == UP)
    wall->y -= wall->l/5;
  else if (direction == DOWN)
    wall->y += wall->l/5;

  if (wall->y < 0)
    wall->y = 0;
  else if (wall->y + wall->l >= vmi_p.YResolution)
    wall->y = vmi_p.YResolution - wall->l - 1;
}

void destroy_wall(Wall *wall) {
  if (wall)
    free(wall);
}
