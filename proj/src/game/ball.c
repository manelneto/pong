#include <lcom/lcf.h>

#include "ball.h"

#include "../drivers/video_gr.h"

Ball* construct_ball(uint16_t x, uint16_t y) {
    Ball* ball = (Ball*) malloc(sizeof(Ball));

    if (!ball) {
        printf("%s: malloc() error\n", __func__);
        return NULL;
    }

    ball->x = x;
    ball->y = y;

    return ball;
}

int draw_ball(Ball *ball) {
  if (vg_draw_pixel(ball->x, ball->y, 0xffffff)) {
    printf("%s: vg_draw_pixel(ball->x: %d, ball->y: %d, color: 0x%x) error\n", __func__, ball->x, ball->y, 0xffffff);
    return 1;
  }

  return 0;

  /*xpm_map_t xpm = &pic;
  xpm_image_t image;

  if (!xpm_load(xpm, XPM_INDEXED, &image)) {
    printf("%s: xpm_load error\n", __func__);
    return 1;
  }

  if (vc_draw_pixmap(x, y, &image)) {
    printf("%s: vc_draw_pixmap error\n", __func__);
    if (vg_exit()) {
      printf("%s: vg_exit error\n", __func__);
      return 1;
    }
    return 1;
  }*/
}

void destroy_ball(Ball *ball) {
    if (ball)
        free(ball);
}
