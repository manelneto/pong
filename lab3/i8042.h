#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8042 Keyboard.
 */

#define KBD_IRQ 1 /**< @brief Keyboard IRQ line */
#define DELAY_US 20000 /**< @brief to be used with tickdelay(micros_to_ticks(DELAY_US)) */

#endif /* _LCOM_I8042_H */
