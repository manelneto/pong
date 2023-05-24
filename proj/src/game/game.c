#include <lcom/lcf.h>

#include "game.h"

#include "ball.h"
#include "wall.h"

static Ball *ball = NULL;
static Wall *wall = NULL;

int game_start(uint16_t xResolution, uint16_t yResolution) {
  ball = construct_ball(xResolution / 2, yResolution / 2, 1, 1);
  if (!ball) {
    printf("%s: construct_ball(%d, %d, %d, %d) error\n", __func__, xResolution / 2, yResolution / 2, 1, 1);
    return 1;
  }

  wall = construct_wall(0, yResolution / 2 - 25, 50);
  if (!wall) {
    printf("%s: construct_wall(%d, %d, %d) error\n", __func__, 0, yResolution / 2 - 25, 50);
    return 1;
  }

  wall->direction = STOP;

  return 0;
}

int game_draw() {
  if (draw_ball(ball)) {
    printf("%d: draw_ball(ball) error\n", __func__);
    return 1;
  }

  if (draw_wall(wall)) {
    printf("%d: draw_wall(wall) error\n", __func__);
    return 1;
  }

  return 0;
}

int game_timer_ih() {
  move_ball(ball);
  move_wall(wall);

  if (ball->x <= wall->x && (ball->y < wall->y || ball->y > wall->y + wall->l))
    return 1;

  return 0;
}

void game_keyboard_ih(GameKey key) {
  if (key == ARROW_UP)
    wall->direction = UP;
  else if (key == ARROW_DOWN)
    wall->direction = DOWN;
}

void game_mouse_ih() {
  ball->vx *= 2;
  ball->vy *= 2;
}

void game_end() {
  destroy_ball(ball);
  destroy_wall(wall);
}
