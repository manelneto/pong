#include <lcom/lcf.h>
#include <lcom/timer.h>

#include <stdint.h>

#include "i8254.h"

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
	/* To be implemented by the students */
	printf("%s is not yet implemented!\n", __func__);

	return 1;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
	/* To be implemented by the students */
	printf("%s is not yet implemented!\n", __func__);

	return 1;
}

int (timer_unsubscribe_int)() {
	/* To be implemented by the students */
	printf("%s is not yet implemented!\n", __func__);

	return 1;
}

void (timer_int_handler)() {
	/* To be implemented by the students */
	printf("%s is not yet implemented!\n", __func__);
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
	if (timer != 0 && timer != 1 && timer != 2) {
		printf("%s: <timer> 0 | 1 | 2\n", __func__);
		return 1;
	}

	uint8_t readback_command = TIMER_RB_CMD;
	readback_command |= TIMER_RB_COUNT_;
	readback_command |= TIMER_RB_SEL(timer);

	if (sys_outb(TIMER_CTRL, readback_command)) {
		printf("%s: sys_outb error\n", __func__);
		return 1;
	}
	
	if (util_sys_inb(TIMER_0 + timer, st)) {
		printf("%s: util_sys_inb error\n", __func__);
		return 1;
	}
	
	return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
	if (timer != 0 && timer != 1 && timer != 2) {
		printf("%s: <timer> 0 | 1 | 2\n", __func__);
		return 1;
	}

	if (field != tsf_all && field != tsf_initial && field != tsf_mode && field != tsf_base) {
		printf("%s: <field> tsf_all | tsf_initial | tsf_mode | tsf_base\n", __func__);
		return 1;
	}
	
	union timer_status_field_val val;

	switch (field) {
		case tsf_all:
			val.byte = st;
			break;
		case tsf_initial:
			val.in_mode = (st & (BIT(5) | BIT(4))) >> 4;
			break;
		case tsf_mode:
			val.count_mode = (st & (BIT(3) | BIT(2) | BIT(1))) >> 1;
			if (val.count_mode > 5)
				val.count_mode &= (BIT (1) | BIT(0));
			break;
		case tsf_base:
			val.bcd = st & TIMER_BCD;
			break;
	}
	
	if (timer_print_config(timer, field, val)) {
		printf("%s: timer_print_config error\n");
		return 1;
	}
	
	return 0;
}
