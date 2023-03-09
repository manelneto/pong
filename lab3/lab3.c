#include <lcom/lcf.h>

#include <lcom/lab3.h>

#include <stdbool.h>
#include <stdint.h>

#include "keyboard.h"

#define ESC 0x81

extern uint32_t cnt;
extern struct scancode code;

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
              kbd_print_scancode(code.makecode, code.size, code.bytes);
              if (code.bytes[0] == ESC)
                esc = true;
              if (keyboard_restore()) {
                printf("%s: keyboard_restore error\n");
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
    printf("%s: kbd_print_no_sysinb error\n", __func__);
		return 1;
  }

  return 0;
}

int(kbd_test_poll)() {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}

int(kbd_test_timed_scan)(uint8_t n) {
  /* To be completed by the students */
  printf("%s is not yet implemented!\n", __func__);

  return 1;
}
