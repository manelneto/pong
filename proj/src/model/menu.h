#ifndef _MENU_H_
#define _MENU_H_

#include <stdint.h>
#include <stdbool.h>

/** @defgroup menu menu
 * @{
 * 
 * Functions related to the menu
*/

/**
 * @brief Starts the menu
 * 
 * Constroys the buttons (play and quit) and the cursor.
 * 
 * @param xResolution horizontal resolution of the screen in pixels
 * @param yResolution vertical resolution of the screen in pixels
 * @return Return 0 upon success and non-zero otherwise
*/
int start_menu(uint16_t xResolution, uint16_t yResolution);

/**
 * @brief Handles a interrupt from the keyboard when in the menu state
 * 
 * Updates buttons
*/
void keyboard_menu_handler();

/**
 * 
*/
void mouse_menu_handler();

/**
 * 
*/
bool check_play();

/**
 * 
*/
bool check_quit();

/**
 * @brief Ends the menu
 * 
 * Destroys the buttons (play and quit) and the cursor.
*/
void end_menu();


/**@}*/

#endif /* _MENU_H_ */
