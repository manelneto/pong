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

void (kbc_ih)() {
	uint8_t output;
	if (kbc_read_output(&output)) {
		code.size = 0;
		return;
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
}

int (keyboard_restore()) {
	code.size = 0;
	code.bytes[0] = 0;
	return 0;
}
