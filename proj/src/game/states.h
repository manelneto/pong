#ifndef _STATES_H_
#define _STATES_H_

#include <stdint.h>

/** @defgroup states states
 * @{
 * 
 * Functions related to the states
*/

/**
 * @brief Enum for the states
 */
typedef enum {
  MENU, /*!< menu */
  GAME, /*!< game */
  EXIT  /*!< exit */
} State;

/**
 * 
*/
int menu_to_game();

/**
 * 
*/
int game_to_menu();

/**@}*/

#endif /* _STATES_H_ */
