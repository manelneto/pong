#include <lcom/lcf.h>

#include <stdint.h>

uint32_t cnt;

int(util_get_LSB)(uint16_t val, uint8_t *lsb) {
	*lsb = (uint8_t) val;
	return 0;
}

int(util_get_MSB)(uint16_t val, uint8_t *msb) {
	*msb = (uint8_t) (val >> 8);
	return 0;
}

int (util_sys_inb)(int port, uint8_t *value) {
	uint32_t v;

	if (sys_inb(port, &v)) {
		printf("%s: sys_inb error\n", __func__);
		return 1;
	}
	
	#ifdef LAB3
	cnt++;
	#endif

	*value = (uint8_t) v;

	return 0;
}
