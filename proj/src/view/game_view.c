#include <lcom/lcf.h>

#include "game_view.h"

#include "../model/game.h"

#include "sprite_view.h"
#include "ball_view.h"
#include "wall_view.h"

extern Ball *ball;
extern Wall *wall;
extern uint32_t score;

int draw_game() {
  if (draw_number(score)) {
    printf("%s: draw_number(score: %d) error\n", __func__, score);
    return 1;
  }

  if (draw_ball(ball)) {
    printf("%s: draw_ball(ball) error\n", __func__);
    return 1;
  }

  if (draw_wall(wall)) {
    printf("%s: draw_wall(wall) error\n", __func__);
    return 1;
  }

  return 0;
}
