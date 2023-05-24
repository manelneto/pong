#ifndef _BUTTON_H_
#define _BUTTON_H_

#include <stdint.h>

/** @defgroup button button
 * @{
 *
 * Functions related to the menu buttons
 */

/**
 * @brief Struct for the button
 */
typedef struct {
  uint16_t x; /*!< horizontal coordinate of the button (top-left corner) */
  uint16_t y; /*!< vertical coordinate of the button (top-left corner) */
  uint8_t w;  /*!< width of the button */
  uint8_t h;  /*!< height of the button */
} Button;

/**
 * @brief Button constructor
 *
 * @param x horizontal coordinate of the button (top-left corner)
 * @param y vertical coordinate of the button (top-left corner)
 * @param w width of the button
 * @param h height of the button
 * @return Constructed button on success, NULL otherwise
 */
Button *construct_button(int16_t x, int16_t y, uint8_t w, uint8_t h);

/**
 * @brief Button drawer
 *
 * @param button pointer to the button to be drawn
 */
int draw_button(Button *button);

/**
 * @brief Button destructor
 *
 * @param button pointer to the button to be destroyed
 */
void destroy_button(Button *button);

/**@}*/

#endif /* _BUTTON_H_ */
