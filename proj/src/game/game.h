#ifndef _GAME_H_
#define _GAME_H_

/** @defgroup game game
 * @{
 * 
 * Functions related to the game
*/

/**
 * @brief Enum for the game states
*/
typedef enum {
    MENU,         /*!< main menu */
    SINGLEPLAYER, /*!< single player mode */
    QUIT          /*!< quit */
} GameState;

/**
 * @brief Starts the game
 * 
 * Subscribes interrupts and configures the devices as needed.
 * 
 * @param mode graphics mode to be set
 * @return Return 0 upon success and non-zero otherwise
*/
int start(uint16_t mode);

/**
 * @brief Game loop
 * 
 * Handles interrupts from devices
*/
void loop();

/**
 * @brief Ends the game
 * 
 * Unsubscribes interrupts and resets the devices.
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int end();

/**@}*/

#endif /* _GAME_H_ */
