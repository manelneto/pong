#include <lcom/lcf.h>

#include "game.h"

#include <lcom/timer.h>
#include "../drivers/keyboard.h"
#include "../drivers/mouse.h"
#include "../drivers/video_gr.h"

#include "ball.h"
#include "wall.h"

static uint8_t timer_irq_set;
static uint8_t keyboard_irq_set;
static uint8_t mouse_irq_set;

extern scancode code;

int start(uint16_t mode) {
  if (timer_subscribe_int(&timer_irq_set)) {
    printf("%s: timer_subscribe_int() error\n", __func__);
    return 1;
  }

  if (keyboard_subscribe_int(&keyboard_irq_set)) {
    printf("%s: keyboard_subscribe_int() error\n", __func__);
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

  if (!vg_init(mode)) {
    printf("%s: vg_init(mode: 0x%x) error\n", __func__, mode);
    return 1;
  }

  return 0;
}

void play() {
  Ball *ball = construct_ball(vmi_p.XResolution/2, vmi_p.YResolution/2, rand() % 10 + 1, rand() % 10 + 1);
  Wall *wall = construct_wall(0, vmi_p.YResolution/2 - 25, 50);

  if (!ball) return;

  int ipc_status, r;
  message msg;

  bool esc = false;

  while (!esc) {
    update_ball(ball);

    if ((r = driver_receive(ANY, &msg, &ipc_status))) {
      printf("%s: driver_receive failed with: %d\n", __func__, r);
      continue;
    }
    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & BIT(timer_irq_set))
            timer_int_handler();
          if (msg.m_notify.interrupts & BIT(keyboard_irq_set)) {
            kbc_ih();
            if (code.size > 0) {
              if (code.bytes[0] == KBD_ESC_BREAKCODE)
                esc = true;
              else if ((code.size == 2 && code.bytes[1] == KBD_ARROW_UP_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_W_MAKECODE))
                move_wall_up(wall);
              else if ((code.size == 2 && code.bytes[1] == KBD_ARROW_DOWN_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_S_MAKECODE))
                move_wall_down(wall);
              keyboard_restore();
            }
            //move_wall_up(wall);
            /*if (code.size > 0) {
              if (code.bytes[0] == KBD_ARROW_UP_MAKECODE_LSB ||  code.bytes[0] == KBD_W_MAKECODE) {
                move_wall_up(wall);
                keyboard_restore();
              }
              else if ((code.size == 2 && code.bytes[0] == KBD_ARROW_DOWN_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_S_MAKECODE)) {
                move_wall_down(wall);
                keyboard_restore();
              }*/
          }
          if (msg.m_notify.interrupts & BIT(mouse_irq_set))
            mouse_ih();
      }
    }

    draw_ball(ball);
    draw_wall(wall);
  }
}

int end() {
  if (vg_exit()) {
    printf("%s: vg_exit() error\n", __func__);
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

  if (keyboard_unsubscribe_int()) {
    printf("%s: keyboard_unsubscribe_int() error\n", __func__);
    return 1;
  }

  if (timer_unsubscribe_int()) {
    printf("%s: timer_unsubscribe_int() error\n", __func__);
    return 1;
  }

  return 0;
}
