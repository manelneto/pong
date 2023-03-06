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

/* I/O port addresses */

#define KBC_ST_REG 0x64 /**< @brief KBC status register */
#define KBC_CMD_REG 0x64 /**< @brief KBC command register */
#define KBC_ARG_REG 0x60 /**< @brief KBC arguments register */
#define KBC_OUT_BUF 0x60 /**< @brief KBC output buffer */

/** STATUS REGISTER FORMAT */

#define KBC_OBF BIT(0) /**< @brief KBC Output buffer full */
#define KBC_IBF BIT(1) /**< @brief KBC Input buffer full */
#define KBC_TIMEOUT_ERROR BIT(6) /**< @brief KBC Timeout error */
#define KBC_PARITY_ERROR BIT(7) /**< @brief KBC Parity error */

#endif /* _LCOM_I8042_H */
