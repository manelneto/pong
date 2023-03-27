#include <lcom/lcf.h>
#include <lcom/lab3.h>

#include "keyboard.h"

#define ESC 0x81

extern struct scancode code;
extern uint32_t cnt;
extern uint32_t counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("PT-PT");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab3/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab3/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(kbd_test_scan)() {
  uint8_t irq_set;

	if (keyboard_subscribe_int(&irq_set)) {
		printf("%s: keyboard_subscribe_int error\n", __func__);
		return 1;
	}

	int ipc_status, r;
	message msg;
  bool esc = false;

	while (!esc) {
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE:
					if (msg.m_notify.interrupts & BIT(irq_set)) { /* subscribed interrupt */
						/* process it */
            kbc_ih();
            if (code.size > 0) {
              if (kbd_print_scancode(code.makecode, code.size, code.bytes)) {
                printf("%s: kbd_print_scancode(code.makecode: %d, code.size: %d, code.bytes) error\n", code.makecode, code.size);
                return 1;
              }
              if (code.bytes[0] == ESC)
                esc = true;
              if (keyboard_restore()) {
                printf("%s: keyboard_restore() error\n");
                return 1;
              }
            }
          }
					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	if (keyboard_unsubscribe_int()) {
		printf("%s: keyboard_unsubscribe_int error\n", __func__);
		return 1;
  }
	
  if (kbd_print_no_sysinb(cnt)) {
    printf("%s: kbd_print_no_sysinb(cnt: %d) error\n", __func__, cnt);
		return 1;
  }

  return 0;
}

int(kbd_test_poll)() {
  bool esc = false;

  while (!esc) {
    if (keyboard_read_scancode_byte()) {
      printf("%s: keyboard_read_scancode_byte() error\n", __func__);
      return 1;
    }
    if (code.size > 0) {
      if (kbd_print_scancode(code.makecode, code.size, code.bytes)) {
        printf("%s: kbd_print_scancode(code.makecode: %d, code.size: %d, code.bytes) error\n", code.makecode, code.size);
        return 1;
      }
      if (code.bytes[0] == ESC)
        esc = true;
      if (keyboard_restore()) {
        printf("%s: keyboard_restore() error\n");
        return 1;
      }
    }
  }

  if (kbd_print_no_sysinb(cnt)) {
    printf("%s: kbd_print_no_sysinb(cnt: %d) error\n", __func__, cnt);
		return 1;
  }

  if (keyboard_enable_interrupts()) {
    printf("%s: keyboard_enable_interrupts() error\n", __func__);
		return 1;
  }

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  uint8_t keyboard_irq_set;
	if (keyboard_subscribe_int(&keyboard_irq_set)) {
		printf("%s: keyboard_subscribe_int error\n", __func__);
		return 1;
	}

  uint8_t timer_irq_set;
  if (timer_subscribe_int(&timer_irq_set)) {
    printf("%s: timer_subscribe_int error\n", __func__);
		return 1;
  }

	int ipc_status, r;
	message msg;
  bool esc = false;

	while (!esc && counter < n * 60) {
		/* Get a request message. */
		if ( (r = driver_receive(ANY, &msg, &ipc_status)) != 0 ) {
			printf("driver_receive failed with: %d", r);
			continue;
		}
		if (is_ipc_notify(ipc_status)) { /* received notification */
			switch (_ENDPOINT_P(msg.m_source)) {
				case HARDWARE:
          if (msg.m_notify.interrupts & BIT(timer_irq_set)) { /* Timer0 int? */
            /* process Timer0 interrupt request */
            timer_int_handler();
          }
					if (msg.m_notify.interrupts & BIT(keyboard_irq_set)) { /* KBD int? */
						/* process KBD interrupt request */
            kbc_ih();
            if (code.size > 0) {
              if (kbd_print_scancode(code.makecode, code.size, code.bytes)) {
                printf("%s: kbd_print_scancode(code.makecode: %d, code.size: %d, code.bytes) error\n", code.makecode, code.size);
                return 1;
              }
              if (code.bytes[0] == ESC)
                esc = true;
              if (keyboard_restore()) {
                printf("%s: keyboard_restore() error\n");
                return 1;
              }
            }
            counter = 0;
          }
					break;
				default:
					break; /* no other notifications expected: do nothing */
			}
		} else { /* received a standard message, not a notification */
			/* no standard messages expected: do nothing */
		}
	}

	if (keyboard_unsubscribe_int()) {
		printf("%s: keyboard_unsubscribe_int error\n", __func__);
		return 1;
  }

  if (timer_unsubscribe_int()) {
    printf("%s: timer_unsubscribe_int error\n", __func__);
		return 1;
  }

  return 0;
}
