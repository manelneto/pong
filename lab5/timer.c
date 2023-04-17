#include <lcom/lcf.h>
#include <lcom/timer.h>

#include "i8254.h"

uint32_t counter = 0;
int32_t timer_hook_id = TIMER0_IRQ;

int (timer_set_frequency)(uint8_t timer, uint32_t freq) {
	if (freq < TIMER_MIN_FREQ) {
		printf("%s: freq < TIMER_MIN_FREQ\n", __func__);
		return 1;
	}
	
	if (freq > TIMER_FREQ) {
		printf("%s: freq > TIMER_FREQ\n", __func__);
		return 1;
	}

	uint8_t st;

	if (timer_get_conf(timer, &st)) {
		printf("%s: timer_get_conf(timer: %d, st: 0x%x) error\n", __func__, timer, st);
		return 1;
	}

	uint8_t control_word = st;
	control_word &= (TIMER_COUNT_MODE | TIMER_BCD);

	control_word |= TIMER_LSB_MSB;
	control_word |= TIMER_SEL(timer);

	if (sys_outb(TIMER_CTRL, control_word)) {
		printf("%s: sys_outb(TIMER_CTRL, control_word: 0x%x) error\n", __func__, control_word);
		return 1;
	}

	uint16_t value = TIMER_FREQ / freq;

	uint8_t lsb;
	if (util_get_LSB(value, &lsb)) {
		printf("%s: util_get_LSB(value: %d, lsb: %d) error\n", __func__, value, lsb);
		return 1;
	}

	uint8_t msb;
	if (util_get_MSB(value, &msb)) {
		printf("%s: util_get_MSB(value: %d, msb: %d) error\n", __func__, value, msb);
		return 1;
	}

	if (sys_outb(TIMER_PORT(timer), lsb)) {
		printf("%s: sys_outb(TIMER_PORT(timer: %d), lsb: %d) error\n", __func__, timer, lsb);
		return 1;
	}

	if (sys_outb(TIMER_PORT(timer), msb)) {
		printf("%s: sys_outb(TIMER_PORT(timer: %d), msb: %d) error\n", __func__, timer, msb);
		return 1;
	}

	return 0;
}

int (timer_subscribe_int)(uint8_t *bit_no) {
	*bit_no = timer_hook_id;

	if (sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, &timer_hook_id)) {
		printf("%s: sys_irqsetpolicy(TIMER0_IRQ, IRQ_REENABLE, timer_hook_id: %d) error\n", __func__, timer_hook_id);
		return 1;
	}

	return 0;
}

int (timer_unsubscribe_int)() {
	if (sys_irqrmpolicy(&timer_hook_id)) {
		printf("%s: sys_irqrmpolicy(timer_hook_id: %d) error\n", __func__, timer_hook_id);
		return 1;
	}
	return 0;
}

void (timer_int_handler)() {
	counter++;
}

int (timer_get_conf)(uint8_t timer, uint8_t *st) {
	uint8_t readback_command = TIMER_RB_CMD;
	readback_command |= TIMER_RB_COUNT_;
	readback_command |= TIMER_RB_SEL(timer);

	if (sys_outb(TIMER_CTRL, readback_command)) {
		printf("%s: sys_outb(TIMER_CTRL, readback_command: 0x%x) error\n", __func__, readback_command);
		return 1;
	}
	
	if (util_sys_inb(TIMER_PORT(timer), st)) {
		printf("%s: util_sys_inb(TIMER_PORT(timer: %d), st: 0x%x) error\n", __func__, timer, st);
		return 1;
	}
	
	return 0;
}

int (timer_display_conf)(uint8_t timer, uint8_t st, enum timer_status_field field) {
	union timer_status_field_val val;

	switch (field) {
		case tsf_all:
			val.byte = st;
			break;
		case tsf_initial:
			val.in_mode = (st & TIMER_IN_MODE) >> 4;
			break;
		case tsf_mode:
			val.count_mode = (st & TIMER_COUNT_MODE) >> 1;
			if (val.count_mode > 5)
				val.count_mode &= TIMER_COUNT_MODE_DONT_CARE;
			break;
		case tsf_base:
			val.bcd = st & TIMER_BCD;
			break;
	}
	
	if (timer_print_config(timer, field, val)) {
		printf("%s: timer_print_config(timer: %d, field, val) error\n", __func__, timer);
		return 1;
	}
	
	return 0;
}
