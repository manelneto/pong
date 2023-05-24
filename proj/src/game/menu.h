#ifndef _MENU_H_
#define _MENU_H_

#include <stdint.h>

/** @defgroup menu menu
 * @{
 * 
 * Functions related to the menu
*/

typedef enum {
    PLAY,
    QUIT,
    ENTER
} MenuKey;

/**
 * @brief Starts the menu
 * 
 * Constroys the buttons (play and quit) and the cursor.
 * 
 * @param xResolution horizontal resolution of the screen in pixels
 * @param yResolution vertical resolution of the screen in pixels
 * @return Return 0 upon success and non-zero otherwise
*/
int menu_start(uint16_t xResolution, uint16_t yResolution);

/**
 * @brief Draws the menu (in the current state)
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int menu_draw();

/**
 * @brief Draws the menu cursor (in the current state)
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int menu_draw_cursor();

/**
 * @brief Handles a interrupt from the timer when in the menu state
 * 
 * Updates game state: moves the cursor.
*/
void menu_timer_ih();

/**
 * @brief Handles a interrupt from the keyboard when in the menu state
 * 
 * Updates selected option.
 * 
 * @param key key pressed
*/
void menu_keyboard_ih(MenuKey key);

/**
 * @brief Handles a interrupt from the mouse when in the game state
 * 
 * Checks if a button is selected and acts accordingly to the selected button action.
 * 
 * @param x horizontal coordinate of the cursor
 * @param y vertical coordinate of the cursor
 * @param lb left button of the cursor pressed
*/
void menu_mouse_ih(uint16_t x, uint16_t y, bool lb);

/**
 * @brief Ends the menu
 * 
 * Destroys the buttons (play and quit) and the cursor.
*/
void menu_end();


/**@}*/

#endif /* _MENU_H_ */
