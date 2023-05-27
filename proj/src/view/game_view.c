#include <lcom/lcf.h>

#include "game_view.h"

#include "../model/game.h"

#include "ball_view.h"
#include "wall_view.h"

extern Ball *ball;
extern Wall *wall;

int draw_game() {
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
