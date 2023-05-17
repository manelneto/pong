#include "rtc.h"

#include <lcom/lcf.h>

// RTC constants
#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_IRQ 8
#define RTC_REGISTER_B 0x0B
#define RTC_REGISTER_A 0x0A
#define SECONDS_REG 0x00
#define MINUTES_REG 0x02
#define HOURS_REG 0x04
#define DAY_REG 0x07
#define MONTH_REG 0x08
#define YEAR_REG 0x09
#define RTC_REGISTER_C 0x0C
#define ALARM_INTERRUPT_FLAG 0x20
#define UPDATE_INTERRUPT_FLAG 0x10
#define PERIODIC_INTERRUPT_FLAG 0x40
#define ALARM_INTERRUPT_ENABLE 0x20
#define UPDATE_INTERRUPT_ENABLE 0x10
#define PERIODIC_INTERRUPT_ENABLE 0x40

int32_t rtc_hook_id = RTC_IRQ;

// Function to subscribe RTC interrupts
int rtc_subscribe_int(uint8_t *bit_no) {
    *bit_no = rtc_hook_id;

    if (sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, &rtc_hook_id)) {
        printf("%s: sys_irqsetpolicy(RTC_IRQ, IRQ_REENABLE, rtc_hook_id: %d) error\n", __func__, rtc_hook_id);
        return 1;
    }

    return 0;
}

// Function to unsubscribe RTC interrupts
int rtc_unsubscribe_int() {
    if (sys_irqrmpolicy(&rtc_hook_id)) {
        printf("%s: sys_irqrmpolicy(rtc_hook_id: %d) error\n", __func__, rtc_hook_id);
        return 1;
    }
    return 0;
}

// Helper function to read from RTC register
int rtc_read_register(uint8_t reg, uint8_t *value) {
    if (sys_outb(RTC_ADDR_REG, reg) != 0) {
        printf("%s: sys_outb(RTC_ADDR_REG, reg: 0x%x) failed\n", __func__, reg);
        return 1;
    }

    if (util_sys_inb(RTC_DATA_REG, value) != 0) {
        printf("%s: util_sys_inb(RTC_DATA_REG, value) failed\n", __func__);
        return 1;
    }

    return 0;
}

// Function to get RTC configuration
int rtc_get_conf(uint8_t *st) {
    if (rtc_read_register(RTC_REGISTER_B, st) != 0) {
        printf("%s: rtc_read_register(RTC_REGISTER_B, st: 0x%x) error\n", __func__, *st);
        return 1;
    }
    return 0;
}

// Function to display RTC configuration
int rtc_display_conf(uint8_t st) {
    printf("RTC Configuration:\n");
    printf("  Data mode: %s\n", (st & 0x04) ? "Binary" : "BCD");
    printf("  Time format: %s\n", (st & 0x02) ? "24-hour" : "12-hour");
    return 0;
}

int rtc_test_conf() {
    uint8_t rtc_irq_bit;
    int ipc_status, r;
    message msg;

    if (rtc_subscribe_int(&rtc_irq_bit) != 0) {
        printf("Error subscribing to RTC interrupts.\n");
        return 1;
    }

    uint32_t rtc_irq_set = BIT(rtc_irq_bit);
    
    while (1) {
        if ((r = driver_receive(ANY, &msg, &ipc_status)) != 0) {
            printf("driver_receive failed with: %d", r);
            continue;
        }

        if (is_ipc_notify(ipc_status)) {
            switch (_ENDPOINT_P(msg.m_source)) {
                case HARDWARE:
                    if (msg.m_notify.interrupts & rtc_irq_set) {
                        uint8_t rtc_config;
                        if (rtc_get_conf(&rtc_config) != 0) {
                            printf("Error getting RTC configuration.\n");
                            rtc_unsubscribe_int();
                            return 1;
                        }
                        
                        rtc_display_conf(rtc_config);
                        rtc_unsubscribe_int();
                        return 0;
                    }
                    break;
                default:
                    break;
            }
        }
    }
}

// Function to convert BCD to Binary
uint8_t bcd_to_bin(uint8_t val) {
    return (val & 0x0F) + (val >> 4) * 10;
}

// Function to get RTC time
int rtc_read_time(uint8_t *hours, uint8_t *minutes, uint8_t *seconds) {
    uint8_t st, prev_hours, prev_minutes, prev_seconds;

    if (rtc_get_conf(&st) != 0) {
        printf("%s: rtc_get_conf error\n", __func__);
        return 1;
    }

    do {
        prev_hours = *hours;
        prev_minutes = *minutes;
        prev_seconds = *seconds;

        if (rtc_read_register(SECONDS_REG, seconds) != 0 || rtc_read_register(MINUTES_REG, minutes) != 0 || rtc_read_register(HOURS_REG, hours) != 0) {
            printf("%s: rtc_read_register error\n", __func__);
            return 1;
        }

        if (st & 0x04) { // Binary mode
            *seconds = bcd_to_bin(*seconds);
            *minutes = bcd_to_bin(*minutes);
            *hours = bcd_to_bin(*hours);
        }

    } while (prev_hours != *hours || prev_minutes != *minutes || prev_seconds != *seconds);

    return 0;
}

// Function to display RTC time
int rtc_display_time(uint8_t hours, uint8_t minutes, uint8_t seconds) {
    printf("RTC Time:\n");
    printf("  %02d:%02d:%02d\n", hours, minutes, seconds);
    return 0;
}

// Function to get RTC date
int rtc_read_date(uint8_t *day, uint8_t *month, uint8_t *year) {
    uint8_t st, prev_day, prev_month, prev_year;

    if (rtc_get_conf(&st) != 0) {
        printf("%s: rtc_get_conf error\n", __func__);
        return 1;
    }

    do {
        prev_day = *day;
        prev_month = *month;
        prev_year = *year;

        if (rtc_read_register(DAY_REG, day) != 0 || rtc_read_register(MONTH_REG, month) != 0 || rtc_read_register(YEAR_REG, year) != 0) {
            printf("%s: rtc_read_register error\n", __func__);
            return 1;
        }

        if (st & 0x04) { // Binary mode
            *day = bcd_to_bin(*day);
            *month = bcd_to_bin(*month);
            *year = bcd_to_bin(*year);
        }

    } while (prev_day != *day || prev_month != *month || prev_year != *year);

    return 0;
}

// Function to display RTC date
int rtc_display_date(uint8_t day, uint8_t month, uint8_t year) {
    printf("RTC Date:\n");
    printf("  %02d/%02d/%02d\n", day, month, year);
    return 0;
}

// Function to enable an interrupt
int rtc_enable_interrupt(uint8_t interrupt_flag) {
    uint8_t st;
    if (rtc_read_register(RTC_REGISTER_B, &st) != 0) {
        printf("%s: rtc_read_register(RTC_REGISTER_B) error\n", __func__);
        return 1;
    }

    st |= interrupt_flag;

    if (sys_outb(RTC_ADDR_REG, RTC_REGISTER_B) != 0 || sys_outb(RTC_DATA_REG, st) != 0) {
        printf("%s: sys_outb error\n", __func__);
        return 1;
    }

    return 0;
}

// Function to disable an interrupt
int rtc_disable_interrupt(uint8_t interrupt_flag) {
    uint8_t st;
    if (rtc_read_register(RTC_REGISTER_B, &st) != 0) {
        printf("%s: rtc_read_register(RTC_REGISTER_B) error\n", __func__);
        return 1;
    }

    st &= ~interrupt_flag;

    if (sys_outb(RTC_ADDR_REG, RTC_REGISTER_B) != 0 || sys_outb(RTC_DATA_REG, st) != 0) {
        printf("%s: sys_outb error\n", __func__);
        return 1;
    }

    return 0;
}

// RTC interrupt handler
void rtc_ih() {
    uint8_t st;
    if (rtc_read_register(RTC_REGISTER_C, &st) != 0) {
        printf("%s: rtc_read_register(RTC_REGISTER_C) error\n", __func__);
        return;
    }

    if (st & ALARM_INTERRUPT_FLAG) {
        printf("Alarm interrupt occurred.\n");
        // Handle alarm interrupt
    }

    if (st & UPDATE_INTERRUPT_FLAG) {
        printf("Update interrupt occurred.\n");
        // Handle update interrupt
    }

    if (st & PERIODIC_INTERRUPT_FLAG) {
        printf("Periodic interrupt occurred.\n");
        // Handle periodic interrupt
    }
}
