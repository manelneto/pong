#ifndef _WALL_H_
#define _WALL_H_

#include <stdint.h>

/** @defgroup wall wall
 * @{
 * 
 * Functions related to the wall
*/

/**
 * @brief Enum for the wall movement direction
*/
typedef enum {
    STOP, /*!< no movement */
    UP,   /*!< move up */
    DOWN  /*!< move down */
} Direction;

/**
 * @brief Struct for the wall
*/
typedef struct {
    int16_t x; /*!< horizontal coordinate of the wall */
    int16_t y; /*!< initial vertical coordinate of the wall */
    int16_t l; /*!< length of the wall */
} Wall;

/**
 * @brief wall constructor
 * 
 * @param x horizontal coordinate of the wall
 * @param y initial vertical coordinate of the wall
 * @param l length of the wall
 * @return Constructed wall on success, NULL otherwise
*/
Wall* construct_wall(int16_t x, int16_t y, uint16_t l);

/**
 * @brief Wall drawer
 * 
 * @param wall pointer to the wall to be drawn
 * 
*/
int draw_wall(Wall *wall);

/**
 * @brief Moves wall up/down according to direction
 * 
 * @param wall pointer to the wall to be moved
 * @param direction direction to move the wall
*/
void move_wall(Wall *wall, Direction direction);

/**
 * @brief Wall destructor
 * 
 * @param wall pointer to the wall to be destroyed
*/
void destroy_wall(Wall *wall);

/**@}*/

#endif /* _WALL_H_ */
