#include "rtc.h"

#include <lcom/lcf.h>

// RTC constants
#define RTC_ADDR_REG 0x70
#define RTC_DATA_REG 0x71
#define RTC_IRQ 8
#define RTC_REGISTER_B 0x0B

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

/*
EXAMPLE IH CODE GIVEN IN SLIDES

void rtc_ih(void) {
int cause;
unsigned long regA;
sys_outb(RTC_ADDR_REG, RTC_REG_C);
cause = sys_inb(RTC_DATA_REG, &regA);
if( cause & RTC_UF )
handle_update_int();
if( cause & RTC_AF )
handle_alarm_int();
if( cause & RTC_PF )
handle_periodic_int();
}
*/

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
