#include <lcom/lcf.h>

#include "model/model.h"

#include "view/view.h"

#include "controller/keyboard.h"
#include "controller/mouse.h"
#include "controller/video.h"
#include <lcom/timer.h>

extern SystemState systemState;

uint8_t timer_irq_set;
uint8_t keyboard_irq_set;
uint8_t mouse_irq_set;


int main(int argc, char *argv[]) {
  lcf_set_language("PT-PT");

  lcf_trace_calls("/home/lcom/labs/proj/debug/trace.txt");

  lcf_log_output("/home/lcom/labs/proj/debug/output.txt");

  if (lcf_start(argc, argv))
    return 1;

  lcf_cleanup();

  return 0;
}

int start() {
  if (timer_set_frequency(0, 60)) {
    printf("%s: timer_set_frequency(0, 60) error\n", __func__);
    return 1;
  }

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

  uint16_t mode = 0x115;
  if (!vg_init(mode)) {
    printf("%s: vg_init(mode: 0x%x) error\n", __func__, mode);
    return 1;
  }

  if (start_pong()) {
    printf("%s: start_pong() error\n", __func__);
    return 1;
  }

  if (draw_frame()) {
    printf("%s: draw_frame() error\n", __func__);
    return 1;
  }

  return 0;
}

void loop() {
  int ipc_status, r;
  message msg;

  while (systemState != EXIT) {
    if ((r = driver_receive(ANY, &msg, &ipc_status))) {
      printf("%s: driver_receive failed with: %d\n", __func__, r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & BIT(timer_irq_set)) {
            timer_state_handler();
          }
          if (msg.m_notify.interrupts & BIT(keyboard_irq_set)) {
            keyboard_state_handler();
          }
          if (msg.m_notify.interrupts & BIT(mouse_irq_set)) {
            mouse_state_handler();
          }
      }
    }
  }
}

int end() {
  end_pong();

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

int(proj_main_loop)(int argc, char *argv[]) {
  if (start()) {
    printf("%s: start() error\n", __func__);
    if (end()) {
      printf("%s: end() error\n", __func__);
      return 1;
    }
    return 1;
  }

  loop();

  if (end()) {
    printf("%s: end() error\n", __func__);
    return 1;
  }

  return 0;
}
