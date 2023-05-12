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
    uint16_t x; /*!< horizontal coordinate of the ball */
    uint16_t y; /*!< vertical coordinate of the ball */
    uint16_t a; /*!< angle of movement (with the horizontal, in the degrees) */
} Ball;

/**
 * @brief Ball constructor
 * 
 * @param x horizontal coordinate of the ball
 * @param y vertical coordinate of the ball
 * @param a angle of movement (with the horizontal, in the degrees)
 * @return Constructed ball on success, NULL otherwise
*/
Ball* construct_ball(uint16_t x, uint16_t y, uint16_t a);

/**
 * @breif Ball drawer
 * 
 * @param ball ball to be drawn
 * 
*/
int draw_ball(Ball *ball);

/**
 * @brief Ball destructor
 * 
 * @param ball pointer to the ball to be destroyed
*/
void destroy_ball(Ball *ball);

/**@}*/

#endif /* _BALL_H_ */
