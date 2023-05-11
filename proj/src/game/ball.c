#include <lcom/lcf.h>

#include "ball.h"


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

int draw_ball(uint16_t x, uint16_t y){
    xpm_map_t xpm = &pic;
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
  }
}

void destroy_ball(Ball *ball) {
    if (ball)
        free(ball);
}
