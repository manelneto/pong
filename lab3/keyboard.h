#ifndef __KEYBOARD_H
#define __KEYBOARD_H

#include <stdint.h>

/**
 * @brief Subscribes and enables KBC interrupts
 *
 * @param bit_no address of memory to be initialized with the
 *         bit number to be set in the mask returned upon an interrupt
 * @return Return 0 upon success and non-zero otherwise
 */
int(kbc_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes KBC interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int(kbc_unsubscribe_int)();

/**
 * @brief KBC interrupt handler
 *
 * First, reads the status register and checks if there was some communications error.
 * Second, reads the scancode byte from the output buffer.
 */
void(kbc_ih)();

#endif /* __KEYBOARD_H */