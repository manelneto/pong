#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8042 KBC.
 */

#define KEYBOARD_IRQ     1     /**< @brief Keyboard IRQ line */
#define KBD_DELAY_US     20000 /**< @brief to be used with tickdelay(micros_to_ticks(DELAY_US)) */
#define KBC_MAX_ATTEMPTS 20    /**< @brief maximum number of attempts */

/* I/O port addresses */

#define KBC_STATUS_REG 0x64 /**< @brief KBC status register */
#define KBC_CMD_REG    0x64 /**< @brief KBC command register */
#define KBC_ARG_REG    0x60 /**< @brief KBC arguments register */
#define KBC_OUT_BUF    0x60 /**< @brief KBC output buffer */

/* KBC commands */

#define KBC_READ_CMD        0x20 /**< @brief KBC read command byte */
#define KBC_WRITE_CMD       0x60 /**< @brief KBC write command byte */
#define KBC_CHECK_CMD       0xAA /**< @brief KBC self-test (if OK, returns 0x55; if error, returns 0xFC) */
#define KBC_CHECK_KBD_CMD   0xAB /**< @brief KBC check keyboard interface */
#define KBC_DISABLE_KDB_CMD 0xAD /**< @brief KBC disable KBD interface */
#define KBC_ENABLE_KDB_CMD  0xAE /**< @brief KBC enable KBD interface */

/* KBC command byte */

#define KBC_INT  BIT(0) /**< @brief KBC enable interrupt on OBF, from keyboard */
#define KBC_INT2 BIT(1) /**< @brief KBC enable interrupt on OBF, from mouse */
#define KBC_DIS  BIT(4) /**< @brief KBC disable keyboard interface */
#define KBC_DIS2 BIT(5) /**< @brief KBC disable mouse interface */

/** STATUS REGISTER FORMAT */

#define KBC_OBF           BIT(0) /**< @brief KBC output buffer full */
#define KBC_IBF           BIT(1) /**< @brief KBC input buffer full */
#define KBC_INH           BIT(4) /**< @brief KBC inhibit flag */
#define KBC_TIMEOUT_ERROR BIT(6) /**< @brief KBC timeout error */
#define KBC_PARITY_ERROR  BIT(7) /**< @brief KBC parity error */

/* OTHER */

#define KBD_BREAKCODE          BIT(7) /**< @brief Breakcode bit */
#define KBD_FIRST_OF_TWO_BYTES 0xE0   /**< @brief First byte of two bytes scancode */
#define KBD_ESC_BREAKCODE      0x81   /**< @brief ESC breakcode */

/**@}*/

#endif /* _LCOM_I8042_H */
