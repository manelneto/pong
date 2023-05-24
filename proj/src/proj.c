#include <lcom/lcf.h>

#include "drivers/keyboard.h"
#include "drivers/mouse.h"
#include "drivers/video_gr.h"
#include <lcom/timer.h>

#include "game/game.h"
#include "game/menu.h"
#include "game/states.h"

static uint8_t timer_irq_set;
static uint8_t keyboard_irq_set;
static uint8_t mouse_irq_set;

extern uint32_t counter;
extern scancode code;
extern struct packet mouse_packet;
extern uint8_t packet_index;
extern vbe_mode_info_t vmi_p;

extern State state;

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

  uint16_t mode = 0x110;
  if (!vg_init(mode)) {
    printf("%s: vg_init(mode: 0x%x) error\n", __func__, mode);
    return 1;
  }

  if (menu_start(vmi_p.XResolution, vmi_p.YResolution)) {
    printf("%s: menu_start(vmi_p.XResolution: %d, vmi_p.YResolution: %d) error\n", __func__, vmi_p.XResolution, vmi_p.YResolution);
    return 1;
  }

  if (menu_draw()) {
    printf("%s: menu_draw() error\n", __func__);
    return 1;
  }

  return 0;
}

void loop() {
  int16_t x = vmi_p.XResolution / 2;
  int16_t y = vmi_p.YResolution / 2;

  int ipc_status, r;
  message msg;

  while (state != EXIT) {
    if ((r = driver_receive(ANY, &msg, &ipc_status))) {
      printf("%s: driver_receive failed with: %d\n", __func__, r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & BIT(timer_irq_set)) {
            timer_int_handler();
            if (state == MENU) {
              menu_timer_ih();
              if (counter % 2 && menu_draw_cursor()) {
                printf("%s: menu_draw_cursor() error\n", __func__);
                state = EXIT;
              }
            } else if (state == GAME) {
              game_timer_ih();
              if (counter % 2 && game_draw()) {
                printf("%s: game_draw() error\n", __func__);
                state = EXIT;
              }
            }
          }
          if (msg.m_notify.interrupts & BIT(keyboard_irq_set)) {
            kbc_ih();
            if (code.size > 0) { // code complete
              if (state == MENU) {
                //menu_keyboard_ih();
              } else if (state == GAME) {
                if ((code.size == 2 && code.bytes[1] == KBD_ARROW_UP_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_W_MAKECODE)) game_keyboard_ih(ARROW_UP);
                else if ((code.size == 2 && code.bytes[1] == KBD_ARROW_DOWN_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_S_MAKECODE)) game_keyboard_ih(ARROW_DOWN);
              }             
              keyboard_restore();
            }
          }
          if (msg.m_notify.interrupts & BIT(mouse_irq_set)) {
            mouse_ih();
            if (packet_index == 3) { // packet complete
              x += mouse_packet.delta_x;
              y -= mouse_packet.delta_y;
              if (state == MENU) {
                menu_mouse_ih(x, y, mouse_packet.lb);
              } else if (state == GAME && mouse_packet.rb) {
                game_mouse_ih();
              }
              mouse_restore();
            }
          }
      }
    }
  }
}

int end() {
  menu_end();

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
