#ifndef RTC_H
#define RTC_H


#include <stdbool.h>
#include <stdint.h>

// Function declarations

int rtc_subscribe_int(uint8_t *bit_no);
int rtc_unsubscribe_int();
int rtc_read_register(uint8_t reg, uint8_t *value);
int rtc_get_conf(uint8_t *st);
int rtc_display_conf(uint8_t st);
int rtc_test_conf();

#endif // RTC_H
