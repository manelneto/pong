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
int rtc_read_time(uint8_t *hours, uint8_t *minutes, uint8_t *seconds);
int rtc_display_time(uint8_t hours, uint8_t minutes, uint8_t seconds);
int rtc_read_date(uint8_t *day, uint8_t *month, uint8_t *year);
int rtc_display_date(uint8_t day, uint8_t month, uint8_t year);
int rtc_enable_interrupt(uint8_t interrupt_flag);
int rtc_disable_interrupt(uint8_t interrupt_flag);
void rtc_ih();

#endif // RTC_H
