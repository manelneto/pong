#include <lcom/lcf.h>
#include <kbc.h>

#include "i8042.h"

int (kbc_read_status)(uint8_t *status) {
	if (util_sys_inb(KBC_STATUS_REG, status)) {
		printf("%s: util_sys_inb(KBC_STATUS_REG, status: 0x%x) error\n", __func__, status);
		return 1;
	}
  return 0;
}

int (kbc_read_output)(uint8_t *output) {
	uint8_t status;
	for (int i = 0; i < KBC_MAX_ATTEMPTS; i++) {
		if (kbc_read_status(&status)) {
			printf("%s: kbc_read_status(status: 0x%x) error\n", __func__, status);
			return 1;
		}

		/* loop while i8042 output buffer is empty */

		if (status & KBC_OBF) {
			if (util_sys_inb(KBC_OUT_BUF, output)) {
				printf("%s: util_sys_inb(KBC_OUT_BUF, output: 0x%x) error\n", __func__, output);
				return 1;
			}

			if ((status & (KBC_PARITY_ERROR | KBC_TIMEOUT_ERROR)) == 0)
				return 0;
			
			return -1;
		}

		if (tickdelay(micros_to_ticks(KBD_DELAY_US))) {
			printf("%s: tickdelay(micros_to_ticks(KBC_DELAY_US)) error\n");
			return 1;
		}
	}
	return 2;
}

int (kbc_write_command)(uint8_t command) {
	uint8_t status;
	for (int i = 0; i < KBC_MAX_ATTEMPTS; i++) {
		if (kbc_read_status(&status)) {
			printf("%s: kbc_read_status(status: 0x%x) error\n", __func__, status);
			return 1;
		}

		/* loop while i8042 input buffer is not empty */

		if ((status & KBC_IBF) == 0) {
			if (sys_outb(KBC_CMD_REG, command)) {
				printf("%s: sys_outb(KBC_CMD_REG, command: 0x%x) error\n", __func__, command);
				return 1;
			}
			return 0;
		}

		if (tickdelay(micros_to_ticks(KBD_DELAY_US))) {
			printf("%s: tickdelay(micros_to_ticks(KBC_DELAY_US)) error\n");
			return 1;
		}
	}
	return 2;
}

int (kbc_write_argument)(uint8_t argument) {
	uint8_t status;
	for (int i = 0; i < KBC_MAX_ATTEMPTS; i++) {
		if (kbc_read_status(&status)) {
			printf("%s: kbc_read_status(status: 0x%x) error\n", __func__, status);
			return 1;
		}

		/* loop while i8042 input buffer is not empty */

		if ((status & KBC_IBF) == 0) {
			if (sys_outb(KBC_ARG_REG, argument)) {
				printf("%s: sys_outb(KBC_ARG_REG, argument: 0x%x) error\n", __func__, argument);
				return 1;
			}
			return 0;
		}

		if (tickdelay(micros_to_ticks(KBD_DELAY_US))) {
			printf("%s: tickdelay(micros_to_ticks(KBC_DELAY_US)) error\n");
			return 1;
		}
	}
	return 2;
}
