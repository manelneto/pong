#ifndef _I8254_H_
#define _I8254_H_

/** @defgroup i8254 i8254
 * @{
 *
 * Constants for programming the i8254 Timer
 */

#define TIMER_FREQ     1193182 /**< @brief Clock frequency for timer in PC and AT */
#define TIMER0_IRQ     0       /**< @brief Timer 0 IRQ line */
#define TIMER_MIN_FREQ 19      /**< @brief Timer lowest possible frequency */

/* I/O port addresses */

#define TIMER_0    0x40 /**< @brief Timer 0 count register */
#define TIMER_1    0x41 /**< @brief Timer 1 count register */
#define TIMER_2    0x42 /**< @brief Timer 2 count register */
#define TIMER_CTRL 0x43 /**< @brief Control register */

#define TIMER_PORT(timer) TIMER_0 + timer /**< @brief Timer count register */

#define SPEAKER_CTRL 0x61 /**< @brief Register for speaker control */

/* Timer control */

/* Timer selection: bits 7 and 6 */

#define TIMER_SEL0   0x00              /**< @brief Control Word for Timer 0 */
#define TIMER_SEL1   BIT(6)            /**< @brief Control Word for Timer 1 */
#define TIMER_SEL2   BIT(7)            /**< @brief Control Word for Timer 2 */
#define TIMER_RB_CMD (BIT(7) | BIT(6)) /**< @brief Read-Back Command */

#define TIMER_SEL(timer) (timer << 6)  /**< @brief Control Word for Timer */

/* Register selection: bits 5 and 4 */

#define TIMER_LSB     BIT(4)                  /**< @brief Initialize Counter LSB only */
#define TIMER_MSB     BIT(5)                  /**< @brief Initialize Counter MSB only */
#define TIMER_LSB_MSB (TIMER_LSB | TIMER_MSB) /**< @brief Initialize LSB first and MSB afterwards */

/* Operating mode: bits 3, 2 and 1 */

#define TIMER_SQR_WAVE (BIT(2) | BIT(1)) /**< @brief Mode 3: square wave generator */
#define TIMER_RATE_GEN BIT(2)            /**< @brief Mode 2: rate generator */

/* Counting mode: bit 0 */

#define TIMER_BCD 0x01 /**< @brief Count in BCD */
#define TIMER_BIN 0x00 /**< @brief Count in binary */

/* Read-Back Command Format */

#define TIMER_RB_COUNT_  BIT(5)       /**< @brief Read-back timer programmed mode */
#define TIMER_RB_STATUS_ BIT(4)       /**< @brief Read-back timer counter value */
#define TIMER_RB_SEL(n)  BIT((n) + 1) /**< @brief Select timer to read-back */

/* Other - Timer */

#define TIMER_IN_MODE              (BIT(5) | BIT(4))          /**< @brief Bitmask for timer counter inicialization */
#define TIMER_COUNT_MODE           (BIT(3) | BIT(2) | BIT(1)) /**< @brief Bitmask for timer counting mode */
#define TIMER_COUNT_MODE_DONT_CARE (BIT (1) | BIT(0))         /**< @brief Bitmask to reset timer counting mode don't care bits */

/**@}*/

#endif /* _I8254_H_ */
