#ifndef _WALL_H_
#define _WALL_H_

#include <stdint.h>

/** @defgroup wall wall
 * @{
 * 
 * Functions related to the wall
*/

/**
 * @brief Struct for the wall
*/
typedef struct {
    int16_t x;  /*!< horizontal coordinate of the wall */
    int16_t yi; /*!< initial vertical coordinate of the wall */
    int16_t yf; /*!< final vertical coordinate of the wall */
} Wall;

/**
 * @brief wall constructor
 * 
 * @param x horizontal coordinate of the wall
 * @param yi initial vertical coordinate of the wall
 * @param yf final vertical coordinate of the wall
 * @return Constructed wall on success, NULL otherwise
*/
Wall* construct_wall(int16_t x, int16_t yi, int16_t yf);

/**
 * @brief Wall drawer
 * 
 * @param wall wall to be drawn
 * 
*/
int draw_wall(Wall *wall);

/**
 * @brief Updates wall position
*/
void update_wall(Wall *wall);

/**
 * @brief wall destructor
 * 
 * @param wall pointer to the wall to be destroyed
*/
void destroy_wall(Wall *wall);

/**@}*/

#endif /* _WALL_H_ */
