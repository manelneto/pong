#ifndef _MODEL_H_
#define _MODEL_H_

/**
 * @brief Enum for the system states
 */
typedef enum {
  RUNNING, /*!< menu */
  EXIT  /*!< exit */
} SystemState;

/**
 * @brief Enum for the game states
 */
typedef enum {
  MENU, /*!< menu */
  GAME, /*!< game */
  END   /*!< end */
} GameState;

int start_pong();
void timer_state_handler();
void keyboard_state_handler();
void mouse_state_handler();
void end_pong();

#endif /* _MODEL_H_ */
