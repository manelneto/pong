#ifndef __MOUSE_H
#define __MOUSE_H

#include <stdint.h>

/** @defgroup mouse mouse
 * @{
 *
 * Functions for using the mouse
 */

/**
 * @brief Subscribes and enables mouse interrupts
 *
 * @param bit_no address of memory to be initialized with the bit number to be set in the mask returned upon an interrupt
 * @return Return 0 upon success and non-zero otherwise
 */
int(mouse_subscribe_int)(uint8_t *bit_no);

/**
 * @brief Unsubscribes mouse interrupts
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int(mouse_unsubscribe_int)();

/**
 * @brief Reads the packet byte from the output buffer
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int(mouse_read_packet_byte)();

/**
 * @brief mouse interrupt handler
 *
 * Calls mouse_read_packet().
 */
void(mouse_ih)();

/**
 * @brief Restores mouse (resets packet)
 *
 * @return Return 0 upon success and non-zero otherwise
 */
int(mouse_restore)();

/**
 * @brief Writes mouse command
 * 
 * @return Return 0 upon success and non-zero otherwise
*/
int (mouse_write_command)(uint8_t command);

/**
 * @brief Enables or disables mouse data reporting
 * 
 * @param enable true if the desired action is to enable mouse data reporting, false if the desired action is to disable mouse data reporting
 * @return Return 0 upon success and non-zero otherwise
*/
int (mouse_data_reporting)(bool enable);

#endif /* __MOUSE_H */
