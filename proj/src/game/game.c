#include <lcom/lcf.h>

#include "game.h"

#include <lcom/timer.h>
#include "../drivers/keyboard.h"
#include "../drivers/mouse.h"
#include "../drivers/video_gr.h"

uint8_t mouse_irq_set;
uint8_t keyboard_irq_set;
uint8_t timer_irq_set;

int start(uint16_t mode) {
    if (!vg_init(mode)) {
        printf("%s: vg_init(mode: 0x%x) error\n", __func__, mode);
        return 1;
    }

    if (mouse_data_reporting(true)) {
        printf("%s: mouse_data_reporting(true) error\n", __func__);
        return 1;
    }

    if (mouse_subscribe_int(&mouse_irq_set)) {
        printf("%s: mouse_subscribe_int() error\n", __func__);
        return 1;
    }

    if (keyboard_subscribe_int(&keyboard_irq_set)) {
        printf("%s: keyboard_subscribe_int() error\n", __func__);
        return 1;
    }

    if (timer_subscribe_int(&timer_irq_set)) {
        printf("%s: timer_subscribe_int() error\n", __func__);
        return 1;
    }

    return 0;
}

int end() {
    if (timer_unsubscribe_int()) {
        printf("%s: timer_unsubscribe_int() error\n", __func__);
        return 1;
    }

    if (keyboard_unsubscribe_int()) {
        printf("%s: keyboard_unsubscribe_int() error\n", __func__);
        return 1;
    }

    if (mouse_unsubscribe_int()) {
        printf("%s: mouse_unsubscribe_int() error\n", __func__);
        return 1;
    }

    if (mouse_data_reporting(false)) {
        printf("%s: mouse_data_reporting(false) error\n", __func__);
        return 1;
    }

    if (vg_exit()) {
        printf("%s: vg_exit() error\n", __func__);
        return 1;
    }

    return 0;
}
