#ifndef __MOUSE_H
#define __MOUSE_H

#include <stdint.h>

/** @defgroup mouse mouse
 * @{
 *
 * Functions for using the mouse
 */

/**
 * @brief Enum for state machine to detect logical and symbol
*/
typedef enum {
  INITIAL,     /*!< initial state */
  FIRST_LINE,  /*!< first line state */
  VERTEX,      /*!< vertex state */
  SECOND_LINE, /*!< second line state */
} state_t;

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

/**
 * @brief Detects mouse event for mouse_test_gesture()
 * 
 * Detects mouse events relevant for the gesture to be matched. This is the lower state-machine of a 2-layered state-machine.
 * Please note that this function is not reentrant, and that the contents of the struct whose address is returned is valid only until the next call of this function.
 * 
 * @param pp 	address of a struct packet with a mouse packet (already parsed)
 * @return address of the mouse event detected
*/
struct mouse_ev* (mouse_detect_event_our)(struct packet* pp);

/**
 * @brief Checks event for logical and
 * 
 * @param event address of memory of mouse event to be checked for logical and
 * @param x_len minimum value of the displacement of each line along the x-direction
 * @param tolerance tolerance to tolerate less precise mice
*/
bool (mouse_check_logical_and)(struct mouse_ev *event, uint8_t x_len, uint8_t tolerance);

#endif /* __MOUSE_H */
