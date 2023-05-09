#ifndef _BALL_H_
#define _BALL_H_

#include <stdint.h>

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
    uint16_t r; /*!< radius of the ball */
} Ball;

/**
 * @brief Ball constructor
 * 
 * @param x horizontal coordinate of the ball
 * @param y vertical coordinate of the ball
 * @param r radius of the ball
 * @return Constructed ball
*/
Ball* construct_ball(uint16_t x, uint16_t y, uint16_t r);

/**
 * @brief Ball destructor
 * 
 * @param ball pointer to the ball to be destroyed
*/
void destroy_ball(Ball *ball);

/**@}*/

#endif /* _BALL_H_ */
