#ifndef _BALL_H_
#define _BALL_H_

#include <stdint.h>

static xpm_row_t const pic[] = {
  "32 13 4",
  "  0",
  "x * #FFFFFF",
"          ****          ",
"      **********      ",
"    **************    ",
"  ********************  ",
" *********************** ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" ************************* ",
" *********************** ",
"    **************    ",
"      **********      ",
"          ****          ",
};

/** @defgroup ball ball
 * @{
 * 
 * Functions related to the ball
*/

/**
 * @brief Struct for the ball
*/
typedef struct {
    int16_t x; /*!< horizontal coordinate of the ball */
    int16_t y; /*!< vertical coordinate of the ball */
    int16_t vx; /*!< horizontal velocity of the ball */
    int16_t vy; /*!< vertical velocity of the ball */
} Ball;

/**
 * @brief Ball constructor
 * 
 * @param x horizontal coordinate of the ball
 * @param y vertical coordinate of the ball
 * @param vx horizontal velocity of the ball
 * @param vy vertical velocity of the ball
 * @return Constructed ball on success, NULL otherwise
*/
Ball* construct_ball(int16_t x, int16_t y, int16_t vx, int16_t vy);

/**
 * @brief Ball drawer
 * 
 * @param ball pointer to the ball to be drawn
*/
int draw_ball(Ball *ball);

/**
 * @brief Updates ball position and velocity
 * 
 * @param ball pointer to the ball to be updated/moved
*/
void move_ball(Ball *ball);

/**
 * @brief Ball destructor
 * 
 * @param ball pointer to the ball to be destroyed
*/
void destroy_ball(Ball *ball);

/**@}*/

#endif /* _BALL_H_ */
