#include <lcom/lcf.h>

#include "drivers/keyboard.h"
#include "drivers/mouse.h"
#include "drivers/video_gr.h"
#include <lcom/timer.h>

#include "game/game.h"

static uint8_t timer_irq_set;
static uint8_t keyboard_irq_set;
static uint8_t mouse_irq_set;

extern uint32_t counter;
extern scancode code;
extern struct packet mouse_packet;
extern vbe_mode_info_t vmi_p;

/**
 * @brief Enum for the states
 */
typedef enum {
  MENU,         /*!< main menu */
  SINGLEPLAYER, /*!< single player mode */
  QUIT          /*!< quit */
} State;

State state = SINGLEPLAYER;

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

  if (game_start(vmi_p.XResolution, vmi_p.YResolution)) {
    printf("%s: game_start(vmi_p.XResolution: %d, vmi_p.YResolution: %d) error\n", __func__, vmi_p.XResolution, vmi_p.YResolution);
    return 1;
  }

  return 0;
}

// apontadores para funções !!!
// separar lógica
// double buffer

void loop() {
  int ipc_status, r;
  message msg;

  bool end = false;

  while (!end) {
    if ((r = driver_receive(ANY, &msg, &ipc_status))) {
      printf("%s: driver_receive failed with: %d\n", __func__, r);
      continue;
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {
        case HARDWARE:
          if (msg.m_notify.interrupts & BIT(timer_irq_set)) {
            timer_int_handler();
            if (counter % 2) {
              if (vg_clean(0, 0, vmi_p.XResolution, vmi_p.YResolution)) {
                printf("%s: vg_clean(%d, %d, vmi_p.XResolution: %d, vmi_p.YResolution: %d) error\n", __func__, 0, 0, vmi_p.XResolution, vmi_p.YResolution);
                end = true;
              }
            }
            if (state == SINGLEPLAYER && game_timer_ih(counter))
              end = true;
          }
          if (msg.m_notify.interrupts & BIT(keyboard_irq_set)) {
            kbc_ih();
            if (code.size > 0) {
              if (code.bytes[0] == KBD_ESC_BREAKCODE)
                end = true;
              else if (state == SINGLEPLAYER) {
                if ((code.size == 2 && code.bytes[1] == KBD_ARROW_UP_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_W_MAKECODE))
                  game_keyboard_ih(ARROW_UP);
                else if ((code.size == 2 && code.bytes[1] == KBD_ARROW_DOWN_MAKECODE_LSB) || (code.size == 1 && code.bytes[0] == KBD_S_MAKECODE))
                  game_keyboard_ih(ARROW_DOWN);
              }
              keyboard_restore();
            }
          }
          if (msg.m_notify.interrupts & BIT(mouse_irq_set)) {
            mouse_ih();
            if (state == SINGLEPLAYER && mouse_packet.lb)
              game_mouse_ih(true);
          }
      }
    }
  }
}

int end() {
  game_end();

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
