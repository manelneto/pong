#include <lcom/lcf.h>
#include "keyboard.h"
#include "kbc.h"

#include <stdint.h>

#include "i8042.h"

struct scancode code;
int32_t keyboard_hook_id = KEYBOARD_IRQ;

int (keyboard_subscribe_int)(uint8_t *bit_no) {
	*bit_no = keyboard_hook_id;

	if (sys_irqsetpolicy(KEYBOARD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &keyboard_hook_id)) {
		printf("%s: sys_irqsetpolicy error\n", __func__);
		return 1;
	}

	return 0;
}

int (keyboard_unsubscribe_int)() {
	if (sys_irqrmpolicy(&keyboard_hook_id)) {
		printf("%s: sys_irqrmpolicy error\n", __func__);
		return 1;
	}
	return 0;
}

int (keyboard_read_scancode_byte()) {
	uint8_t output;
	int r = kbc_read_output(&output);
	if (r == -1) {
		keyboard_restore();
		printf("%s: kbc_read_output error (returned %d)\n", __func__, r);
		return 1;
	} else if (r == 2) {
		keyboard_enable_interrupts();
		printf("%s: kbc_read_output error (returned %d)\n", __func__, r);
		return 1;
	}

	if (output == KBD_FIRST_OF_TWO_BYTES) {
		code.size = 0;
		code.bytes[0] = output;
	} else if (code.bytes[0] != KBD_FIRST_OF_TWO_BYTES) {
		code.size = 1;
		code.bytes[0] = output;
	} else {
		code.size = 2;
		code.bytes[1] = output;
	}

	code.makecode = (bool) !(output & KBD_BREAKCODE);
	return 0;
}

void (kbc_ih)() {
	keyboard_read_scancode();
}

int (keyboard_restore()) {
	code.size = 0;
	code.bytes[0] = 0;
	return 0;
}

int (keyboard_enable_interrupts)() {
	int r;
	if ((r = kbc_write_command(KBC_READ_CMD))) {
    printf("%s: kbc_write_command error (returned %d)\n", __func__, r);
    return 1;
  }

  uint8_t command_byte;
  if ((r = kbc_read_output(&command_byte))) {
    printf("%s: kbc_read_output error (returned %d)\n", __func__, r);
    return 1;
  }

  if ((r = kbc_write_command(KBC_WRITE_CMD))) {
    printf("%s: kbc_write_command error (returned %d)\n", __func__, r);
    return 1;
  }

  if ((r = kbc_write_argument(command_byte | BIT(0)))) {
    printf("%s: kbc_write_command error (returned %d)\n", __func__, r);
    return 1;
  }

	return 0;
}
