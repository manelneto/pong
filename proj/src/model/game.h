#ifndef _GAME_H_
#define _GAME_H_

#include <stdint.h>
#include <stdbool.h>

/** @defgroup game game
 * @{
 * 
 * Functions related to the game
*/

/**
 * @brief Starts the game
 * 
 * Constroys the ball and the wall.
 * 
 * @param xResolution horizontal resolution of the screen in pixels
 * @param yResolution vertical resolution of the screen in pixels
 * @return Return 0 upon success and non-zero otherwise
*/
int start_game(uint16_t xResolution, uint16_t yResolution, uint8_t difficulty);


/**
 * @brief Handles a interrupt from the timer when in the game state
 * 
 * Moves the ball and the wall. Updates game state.
*/
void timer_game_handler();

/**
 * @brief Handles a interrupt from the keyboard when in the game state
 * 
 * Updates wall direction.
*/
void keyboard_game_handler();

/**
 * @brief Handles a interrupt from the mouse when in the game state
 * 
 * Updates ball velocity.
*/
void mouse_game_handler();

/**
 * 
*/
bool check_game_over();

/**
 * @brief Ends the game
 * 
 * Destroys the ball and the wall.
*/
void end_game();

/**@}*/

#endif /* _GAME_H_ */
