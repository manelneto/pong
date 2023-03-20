#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/** @defgroup i8042 i8042
 * @{
 *
 * Constants for programming the i8042 KBC.
 */

#define KEYBOARD_IRQ     1     /**< @brief Keyboard IRQ line */
#define MOUSE_IRQ        12    /**< @brief Mouse IRQ line */
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
#define KBC_DISABLE_MOUSE   0xA7 /**< @brief KBC disable mouse interface */
#define KBC_ENABLE_MOUSE    0xA8 /**< @brief KBC enable mouse interface */
#define KBC_CHECK_MOUSE     0xA9 /**< @brief KBC check mouse interface */
#define KBC_WRITE_TO_MOUSE  0xD4 /**< @brief KBC write byte (argument) to mouse */

/* KBC arguments */

#define KBC_RESET                  0xFF /**< @brief KBC mouse reset */
#define KBC_RESEND                 0xFE /**< @brief KBC for serial communications errors */
#define KBC_SET_DEFAULTS           0xF6 /**< @brief KBC set default values */
#define KBC_DISABLE_DATA_REPORTING 0xF5 /**< @brief KBC disable data reporting (in stream mode, should be sent before any other command) */
#define KBC_ENABLE_DATA_REPORTING  0xF4 /**< @brief KBC enable data reporting (in stream mode only) */
#define KBC_SET_SAMPLE_RATE        0xF3 /**< @brief KBC set state sampling rate */
#define KBC_SET_REMOTE_MODE        0xF0 /**< @brief KBC send data on request only */
#define KBC_READ_DATA              0xEB /**< @brief KBC send data packet request */
#define KBC_SET_STREAM_MODE        0xEA /**< @brief KBC send data on events */
#define KBC_STATUS_REQUEST         0xE9 /**< @brief KBC get mouse configuration (3 bytes) */
#define KBC_SET_RESOLUTION         0xE8 /**< @brief KBC set resolution */
#define KBC_SET_SCALING_2          0xE7 /**< @brief KBC acceleration mode */
#define KBC_SET_SCALING_1          0xE6 /**< @brief KBC linear mode */

/* KBC command byte */

#define KBC_INT  BIT(0) /**< @brief KBC enable interrupt on OBF, from keyboard */
#define KBC_INT2 BIT(1) /**< @brief KBC enable interrupt on OBF, from mouse */
#define KBC_DIS  BIT(4) /**< @brief KBC disable keyboard interface */
#define KBC_DIS2 BIT(5) /**< @brief KBC disable mouse interface */

/* KBC acknowledgment byte */

#define KBC_ACK   0xFA /**< @brief KBC everything OK */
#define KBC_NACK  0xFE /**< @brief KBC if invalid byte (may be because of a serial communication error) */
#define KBC_ERROR 0xFC /**< @brief KBC second consecutive invalid byte */

/** STATUS REGISTER FORMAT */

#define KBC_OBF           BIT(0) /**< @brief KBC output buffer full */
#define KBC_IBF           BIT(1) /**< @brief KBC input buffer full */
#define KBC_SYS           BIT(2) /**< @brief KBC system flag: 0 if system in power-on reset, 1 if system already initialized */
#define KBC_A2            BIT(3) /**< @brief KBC A2 input line: 0 if data byte, 1 if command byte */
#define KBC_INH           BIT(4) /**< @brief KBC inhibit flag */
#define KBC_AUX           BIT(5) /**< @brief KBC mouse data */
#define KBC_TIMEOUT_ERROR BIT(6) /**< @brief KBC timeout error - invalid data */
#define KBC_PARITY_ERROR  BIT(7) /**< @brief KBC parity error - invalid data */

/* OTHER - KEYBOARD */

#define KBD_BREAKCODE          BIT(7) /**< @brief Breakcode bit */
#define KBD_FIRST_OF_TWO_BYTES 0xE0   /**< @brief First byte of two bytes scancode */
#define KBD_ESC_BREAKCODE      0x81   /**< @brief ESC breakcode */

/* OTHER - MOUSE */

#define MOUSE_LB          BIT(0) /**< @brief L.B. */
#define MOUSE_RB          BIT(1) /**< @brief R.B. */
#define MOUSE_MB          BIT(2) /**< @brief M.B. */
#define MOUSE_BYTE1       BIT(3) /**< @brief 1 if byte 1 of mouse packet */
#define MOUSE_MSB_X_DELTA BIT(4) /**< @brief MSB X delta */
#define MOUSE_MSB_Y_DELTA BIT(5) /**< @brief MSB Y delta */
#define MOUSE_X_OVFL      BIT(6) /**< @brief X overflow */
#define MOUSE_Y_OVFL      BIT(7) /**< @brief Y overflow */
#define MOUSE_SET_MSB     0xFF00 /**< @brief to set the most significant byte as 11111111 (complement-to-two)*/

/**@}*/

#endif /* _LCOM_I8042_H */
