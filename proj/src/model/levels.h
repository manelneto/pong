#ifndef _LEVELS_H_
#define _LEVELS_H_

#include <stdint.h>
#include <stdbool.h>

/** @defgroup levels levels
 * @{
 * 
 * Functions related to the levels
*/

/**
 * @brief Starts the levels
 * 
 * Constroys the buttons (easy, medium and hard) and the cursor.
 * 
 * @param xResolution horizontal resolution of the screen in pixels
 * @param yResolution vertical resolution of the screen in pixels
 * @return Return 0 upon success and non-zero otherwise
*/
int start_levels(uint16_t xResolution, uint16_t yResolution);

/**
 * @brief Handles a interrupt from the keyboard when in the levels state
 * 
 * Updates buttons
*/
void keyboard_levels_handler();

/**
 * 
*/
void mouse_levels_handler();

/**
 * 
*/
bool check_easy();

/**
 * 
*/
bool check_medium();

/**
 * 
*/
bool check_hard();

/**
 * @brief Ends the levels
 * 
 * Destroys the buttons (easy, medium and hard) and the cursor.
*/
void end_levels();


/**@}*/

#endif /* _LEVELS_H_ */
