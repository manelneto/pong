#include <lcom/lcf.h>
#include <lcom/lab5.h>

#include <lcom/video_gr.h>
#include "keyboard.h"

#define ESC 0x81

extern struct scancode code;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("PT-PT");

  // enables to log function invocations that are being "wrapped" by LCF
  // [comment this out if you don't want/need it]
  lcf_trace_calls("/home/lcom/labs/lab5/trace.txt");

  // enables to save the output of printf function calls on a file
  // [comment this out if you don't want/need it]
  lcf_log_output("/home/lcom/labs/lab5/output.txt");

  // handles control over to LCF
  // [LCF handles command line arguments and invokes the right function]
  if (lcf_start(argc, argv))
    return 1;

  // LCF clean up tasks
  // [must be the last statement before return]
  lcf_cleanup();

  return 0;
}

int(video_test_init)(uint16_t mode, uint8_t delay) {
  if (!vg_init(mode)) {
    printf("%s: vg_init error\n", __func__);
    return 1;
  }

  if (sleep(delay)) {
    printf("%s: sleep error\n", __func__);
    return 1;
  }

  if (vg_exit()) {
    printf("%s: vg_exit error\n", __func__);
    return 1;
  }

  return 0;
}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y, uint16_t width, uint16_t height, uint32_t color) {
  if (!vg_init(mode)) {
    printf("%s: vg_init error\n", __func__);
    return 1;
  }

  if (vg_draw_rectangle(x, y, width, height, color)) {
    printf("%s: vg_draw_rectangle error\n", __func__);
    return 1;
  }

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

  if (vg_exit()) {
    printf("%s: vg_exit error\n", __func__);
    return 1;
  }

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  /* To be completed */
  printf("%s(0x%03x, %u, 0x%08x, %d): under construction\n", __func__, mode, no_rectangles, first, step);

  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  /* To be completed */
  printf("%s(%8p, %u, %u): under construction\n", __func__, xpm, x, y);

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n", __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
