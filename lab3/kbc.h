#ifndef __KBC_H
#define __KBC_H

#include <stdint.h>

/** @defgroup kbc kbc
 * @{
 *
 * Functions for using the i8042 KBC
 */

/**
 * @brief Reads the KBC status
 * 
 * @param status Address of memory position to be filled with the KBC status
 * @return Return 0 upon success and non-zero otherwise
*/
int (kbc_read_status)(uint8_t *status);

/**
 * @brief Reads the KBC output
 * 
 * @param output Address of memory position to be filled with the KBC output
 * @return Return 0 upon success and non-zero otherwise (-1 if invalid data, 1 if internal error, 2 if exceeded maximum number of attempts to read KBC output)
*/
int (kbc_read_output)(uint8_t *output);

/**
 * @brief Writes command to KBC
 * 
 * @param command Command to be written to KBC
 * @return Return 0 upon success and non-zero otherwise (1 if internal error, 2 if exceeded maximum number of attempts to write command to KBC)
*/
int (kbc_write_command)(uint8_t command);

/**
 * @brief Writes argument to KBC
 * 
 * @param argument Argument to be written to KBC
 * @return Return 0 upon success and non-zero otherwise (1 if internal error, 2 if exceeded maximum number of attempts to write argument to KBC)
*/
int (kbc_write_argument)(uint8_t argument);

#endif /* __KBC_H */
