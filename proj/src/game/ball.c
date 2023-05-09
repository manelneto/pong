#include <lcom/lcf.h>

#include "ball.h"

Ball* construct_ball(uint16_t x, uint16_t y, uint16_t r) {
    Ball* ball = (Ball*) malloc(sizeof(Ball));

    if (!ball) {
        printf("%s: malloc() error\n", __func__);
        return NULL;
    }

    ball->x = x;
    ball->y = y;
    ball->r = r;

    return ball;
}

void destroy_ball(Ball *ball) {
    if (ball)
        free(ball);
}
