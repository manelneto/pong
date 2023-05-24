#ifndef _CURSOR_H_
#define _CURSOR_H_

#include <stdint.h>

/** @defgroup cursor cursor
 * @{
 * 
 * Functions related to the cursor
*/

/**
 * @brief Struct for the cursor
*/
typedef struct {
    uint16_t x; /*!< horizontal coordinate of the cursor */
    uint16_t y; /*!< vertical coordinate of the cursor */
} Cursor;

/**
 * @brief Cursor constructor
 * 
 * @param x horizontal coordinate of the cursor
 * @param y vertical coordinate of the cursor
 * @return Constructed cursor on success, NULL otherwise
*/
Cursor* construct_cursor(uint16_t x, uint16_t y);

/**
 * @brief Cursor drawer
 * 
 * @param cursor pointer to the cursor to be drawn
 * @return Return 0 upon success and non-zero otherwise
*/
int draw_cursor(Cursor *cursor);

/**
 * @brief Cursor destructor
 * 
 * @param cursor pointer to the cursor to be destroyed
*/
void destroy_cursor(Cursor *cursor);

/**@}*/

#endif /* _Cursor_H_ */
