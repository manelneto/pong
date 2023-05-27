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
  uint16_t x;    /*!< horizontal coordinate of the button (top-left corner) */
  uint16_t y;    /*!< vertical coordinate of the button (top-left corner) */
  uint16_t w;     /*!< width of the button */
  uint16_t h;     /*!< height of the button */
  bool selected; /*!< true if the button is selected, false otherwise */
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
Button *construct_button(uint16_t x, uint16_t y, uint16_t w, uint16_t h);

/**
 * @brief Updates button state (selected/unselected) accordingly to cursor coordinates
 * 
 * @param button button to be updated
 * @param x horizontal coordinate of the cursor
 * @param y vertical coordinate of the cursor
 * @return Return 0 upon success and non-zero otherwise
*/
int check_button(Button *button, uint16_t x, uint16_t y);

/**
 * @brief Button destructor
 *
 * @param button pointer to the button to be destroyed
 */
void destroy_button(Button *button);

/**@}*/

#endif /* _BUTTON_H_ */
