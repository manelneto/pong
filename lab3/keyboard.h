#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <stdint.h>

/** @defgroup keyboard keyboard
 * @{
 *
 * Functions for using the keyboard
 */

/**
 * @brief Struct for scancodes
*/
struct scancode {
  bool makecode; /*!< indicates whether this is a make or a break code */
  uint8_t size; /*!< size of the scancode in bytes */
  uint8_t bytes[2]; /*!< array with the bytes of the scancode, in order */
};

/**
 * @brief Subscribes and enables Keyboard interrupts
 *
 * @param bit_no address of memory to be initialized with the bit number to be set in the mask returned upon an interrupt
 * @return Return 0 upon success and non-zero otherwise
 */
int(keyboard_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes Keyboard interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int(keyboard_unsubscribe_int)();

/**
 * @brief Keyboard interrupt handler
 *
 * First, reads the status register and checks if there was some communications error.
 * Second, reads the scancode byte from the output buffer.
 */
void(kbc_ih)();

/**
 * @brief Restores keyboard (resets scancode)
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int(keyboard_restore)();

#endif /* __KEYBOARD_H */
