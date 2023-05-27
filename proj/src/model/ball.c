#include <lcom/lcf.h>

#include "ball.h"

#include "../xpm/ball.xpm"

extern uint32_t score;

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
  ball->sprite = construct_sprite((xpm_map_t) ball_xpm, 0x818181);

  if (!ball->sprite) {
    printf("%s: construct_sprite(ball_xpm, 0x818181) error\n", __func__);
    return NULL;
  }

  return ball;
}

int move_ball(Ball *ball, uint16_t x_max, uint16_t y_max) {
  if (!ball) {
    printf("%s: ball is NULL\n", __func__);
    return 1;
  }

  ball->x += ball->vx;
  ball->y += ball->vy;
  
  if (ball->x <= 0) {
    // choque com o ecrã
    ball->vx = -ball->vx;
    ball->x = 0;
  }

  if (ball->x + ball->sprite->width >= x_max) {
    ball->vx = -ball->vx;
    ball->x = x_max - ball->sprite->width - 1;
  }

  if (ball->y < 0) {
    ball->vy = -ball->vy;
    ball->y = 0;
  } else if (ball->y + ball->sprite->height >= y_max) {
    ball->vy = -ball->vy;
    ball->y = y_max - ball->sprite->height - 1;
  }

  return 0;
}

int (move_ball_after_collision_with_wall)(Ball *ball, Wall *wall) {
  if (!ball) {
    printf("%s: ball is NULL\n", __func__);
    return 1;
  }

  ball->vx = -ball->vx;
  ball->x = wall->x + wall->w;
  return 0;
}

int speedup_ball(Ball *ball) {
  if (abs(ball->vx) < 32 && abs(ball->vy) < 32) {
    ball->vx *= 2;
    ball->vy *= 2;
    return 0;
  }
  return 1;
}

void destroy_ball(Ball *ball) {
  if (ball)
    free(ball);
}
