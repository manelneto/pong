#include <lcom/lcf.h>
#include <keyboard.h>

#include <stdint.h>

#include "i8042.h"

uint32_t cnt = 0;
int32_t hook_id = KBD_IRQ;

int (kbc_subscribe_int)(uint8_t *bit_no) {
	// to be completed
}

int (kbc_unsubscribe_int)() {
	// to be completed
}

void (kbc_ih)() {
	// to be completed
}