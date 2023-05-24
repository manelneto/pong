#ifndef _MODEL_H_
#define _MODEL_H_

#include <stdint.h>

/** @defgroup game game
 * @{
 * 
 * Functions related to the model
*/

/**
 * @brief Enum for the states
 */
typedef enum {
  MENU, /*!< menu */
  GAME, /*!< game */
  EXIT  /*!< exit */
} State;

int menu_to_game();

int game_to_menu();

/**@}*/

#endif /* _MODEL_H_ */
