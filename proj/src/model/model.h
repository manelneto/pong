#ifndef _MODEL_H_
#define _MODEL_H_

/**
 * @brief Enum for the states
 */
typedef enum {
  MENU,   /*!< menu */
  LEVELS, /*!< levels */
  GAME,   /*!< game */
  END     /*!< end */
} State;

int start_pong();
void timer_interrupt_handler();
void keyboard_interrupt_handler();
void mouse_interrupt_handler();
void end_pong();

#endif /* _MODEL_H_ */
