#include <lcom/lcf.h>
#include <kbc.h>

#include "i8042.h"

int (kbc_read_status)(uint8_t *status) {
	if (util_sys_inb(KBC_STATUS_REG, status)) {
		printf("%s: util_sys_inb error\n", __func__);
		return 1;
	}
  return 0;
}

int (kbc_read_output)(uint8_t *output) {
  if (util_sys_inb(KBC_OUT_BUF, output)) {
		printf("%s: util_sys_inb error\n", __func__);
		return 1;
	}
  return 0;
}

int (kbc_write_command)(uint8_t command) {
	if (sys_outb(KBC_CMD_REG, command)) {
			printf("%s: sys_outb error\n", __func__);
		return 1;
	}
	return 0;
}
