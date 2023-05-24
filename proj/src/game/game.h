#ifndef _GAME_H_
#define _GAME_H_

/** @defgroup game game
 * @{
 * 
 * Functions related to the game
*/

typedef enum {
    ARROW_UP,
    ARROW_DOWN
} GameKey;

/**
 * @brief Starts the game
 * 
 * Constroys the ball and the wall.
 * 
 * @param xResolution horizontal resolution of the screen in pixels
 * @param yResolution vertical resolution of the screen in pixels
 * @return Return 0 upon success and non-zero otherwise
*/
int game_start(uint16_t xResolution, uint16_t yResolution);

/**
 * @brief Draws the game (in the current state)
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int game_draw();

/**
 * @brief Handles a interrupt from the timer when in the game state
 * 
 * Updates game state: moves the ball and the wall.
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int game_timer_ih();

/**
 * @brief Handles a interrupt from the keyboard when in the game state
 * 
 * Updates wall direction.
 * 
 * @param key key pressed
*/
void game_keyboard_ih(GameKey key);

/**
 * @brief Handles a interrupt from the mouse when in the game state
 * 
 * Updates ball velocity.
*/
void game_mouse_ih();

/**
 * @brief Ends the game
 * 
 * Destroys the ball and the wall.
*/
void game_end();

/**@}*/

#endif /* _GAME_H_ */
