#include <lcom/lcf.h>

#include "ball.h"

#include "../drivers/video_gr.h"

Ball *construct_ball(int16_t x, int16_t y, int16_t vx, int16_t vy) {
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
  if (vg_draw_pixel(ball->x, ball->y, 0xffffff)) {
    printf("%s: vg_draw_pixel(ball->x: %d, ball->y: %d, color: 0x%x) error\n", __func__, ball->x, ball->y, 0xffffff);
    return 1;
  }

  return 0;
}

void move_ball(Ball *ball) {
  ball->x += ball->vx;
  ball->y += ball->vy;

  if (ball->y <= 0 || ball->y >= vmi_p.YResolution) {
    ball->vy = -ball->vy;
  }

  if (ball->x <= 0 || ball->x >= vmi_p.XResolution) {
    ball->vx = -ball->vx;
  }
}

void destroy_ball(Ball *ball) {
  if (ball)
    free(ball);
}
