#include <lcom/lcf.h>

#include "ball.h"

#include "../drivers/video_gr.h"

Ball *construct_ball(uint16_t x, uint16_t y, int8_t vx, int8_t vy) {
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

int draw_ball(Ball *ball) {
  if (!ball) {
    printf("%s: ball is NULL\n", __func__);
    return 1;
  }

  if (vg_draw_pixel(ball->x, ball->y, 0xffffff)) {
    printf("%s: vg_draw_pixel(ball->x: %d, ball->y: %d, color: 0x%x) error\n", __func__, ball->x, ball->y, 0xffffff);
    return 1;
  }

  return 0;
}

int move_ball(Ball *ball) {
  if (!ball) {
    printf("%s: ball is NULL\n", __func__);
    return 1;
  }

  ball->x += ball->vx;
  ball->y += ball->vy;

  if (ball->y < 0) {
    ball->vy = -ball->vy;
    ball->y = 0;
  } else if (ball->y >= vmi_p.YResolution) {
    ball->vy = -ball->vy;
    ball->y = vmi_p.YResolution - 1;
  }

  if (ball->x < 0) {
    ball->vx = -ball->vx;
    ball->x = 0;
  } else if (ball->x >= vmi_p.XResolution) {
    ball->vx = -ball->vx;
    ball->x = vmi_p.XResolution - 1;
  }

  return 0;
}

void destroy_ball(Ball *ball) {
  if (ball)
    free(ball);
}
