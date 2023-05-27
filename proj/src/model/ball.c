#include <lcom/lcf.h>

#include "ball.h"

Ball *construct_ball(int16_t x, int16_t y, int8_t vx, int8_t vy) {
  Ball *ball = (Ball *) malloc(sizeof(Ball));

  if (!ball) {
    printf("%s: malloc() error\n", __func__);
    return NULL;
  }

  ball->x = x;
  ball->y = y;
  ball->vx = vx;
  ball->vy = vy;

  return ball;
}

int move_ball(Ball *ball, uint16_t x_max, uint16_t y_max) {
  if (!ball) {
    printf("%s: ball is NULL\n", __func__);
    return 1;
  }

  printf("ball: (%d, %d, %d, %d), xmax = %d, ymax = %d\n", ball->x, ball->y, ball->vx, ball->vy, x_max, y_max);

  ball->x += ball->vx;
  ball->y += ball->vy;

  if (ball->x < 0) {
    ball->vx = -ball->vx;
    ball->x = 0;
  } else if (ball->x >= x_max) {
    ball->vx = -ball->vx;
    ball->x = x_max - 1;
  }

  if (ball->y < 0) {
    ball->vy = -ball->vy;
    ball->y = 0;
  } else if (ball->y >= y_max) {
    ball->vy = -ball->vy;
    ball->y = y_max - 1;
  }

  return 0;
}

void speedup_ball(Ball *ball) {
  ball->vx *= 2;
  ball->vy *= 2;
}

void destroy_ball(Ball *ball) {
  if (ball)
    free(ball);
}
