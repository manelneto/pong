#include <lcom/lcf.h>

#include "ball_view.h"

#include "../controller/video.h"

int draw_ball(Ball *ball) {
  if (!ball) {
    printf("%s: ball is NULL\n", __func__);
    return 1;
  }

  if (video_draw_pixel(ball->x, ball->y, 0xffffff)) {
    printf("%s: video_draw_pixel(ball->x: %d, ball->y: %d, color: 0x%x) error\n", __func__, ball->x, ball->y, 0xffffff);
    return 1;
  }

  return 0;
}
