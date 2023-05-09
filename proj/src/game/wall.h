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
    uint16_t x;  /*!< horizontal coordinate of the wall */
    uint16_t yi; /*!< initial vertical coordinate of the wall */
    uint16_t yf; /*!< final vertical coordinate of the wall */
} Wall;

/**
 * @brief wall constructor
 * 
 * @param x horizontal coordinate of the wall
 * @param yi initial vertical coordinate of the wall
 * @param yf final vertical coordinate of the wall
 * @return Constructed wall
*/
Wall* construct_wall(uint16_t x, uint16_t yi, uint16_t yf);

/**
 * @brief wall destructor
 * 
 * @param wall pointer to the wall to be destroyed
*/
void destroy_wall(Wall *wall);

/**@}*/

#endif /* _WALL_H_ */