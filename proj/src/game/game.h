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
} Key;

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
 * 
 * 
*/
int game_timer_ih(uint32_t counter);

/**
 * 
*/
void game_keyboard_ih(Key key);

/**
 * 
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
