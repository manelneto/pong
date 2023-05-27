#include <lcom/lcf.h>

#include "game.h"

#include "ball.h"
#include "wall.h"

#include "../controller/keyboard.h"
#include "../controller/mouse.h"

extern scancode code;
extern struct packet mouse_packet;

Ball *ball = NULL;
Wall *wall = NULL;

static uint16_t x_max;
static uint16_t y_max;

int start_game(uint16_t xResolution, uint16_t yResolution, uint8_t difficulty) {
  uint8_t direction = (rand() % 2) ? 1 : -1;
  ball = construct_ball(xResolution / 2, yResolution / 2, 1 * difficulty * direction, 1 * difficulty * direction);
  if (!ball) {
    printf("%s: construct_ball(%d, %d, %d, %d) error\n", __func__, xResolution / 2, yResolution / 2, 1, 1);
    return 1;
  }

  wall = construct_wall(0, yResolution / 2 - 25, 10, 90/difficulty);
  if (!wall) {
    printf("%s: construct_wall(%d, %d, %d) error\n", __func__, 0, yResolution / 2 - 25, 50);
    return 1;
  }

  x_max = xResolution;
  y_max = yResolution;

  return 0;
}

void timer_game_handler() {
  move_ball(ball, wall, x_max, y_max);
}

void keyboard_game_handler() {
  if ((code.size == 2 && code.bytes[1] == KBD_ARROW_UP_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_W_MAKECODE))
    move_wall_up(wall);
  if ((code.size == 2 && code.bytes[1] == KBD_ARROW_DOWN_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_S_MAKECODE))
    move_wall_down(wall, y_max);
}

void mouse_game_handler() {
  if (mouse_packet.rb)
    speedup_ball(ball);
}

bool check_game_over() {
  return ball->x <= wall->x && (ball->y < wall->y || ball->y > wall->y + wall->h);
}

void end_game() {
  destroy_ball(ball);
  destroy_wall(wall);
}
