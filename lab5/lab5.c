#include <lcom/lcf.h>
#include <lcom/lab5.h>
#include <lcom/timer.h>

#include "video_card.h"
#include "keyboard.h"

#define ESC 0x81

extern uint32_t counter;
extern scancode code;

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

int (wait_for_esc)() {
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

  if (vg_draw_rectangle(x, y, width, height, vc_normalize_color(color))) {
    printf("%s: vg_draw_rectangle error\n", __func__);
    if (vg_exit()) {
      printf("%s: vg_exit error\n", __func__);
      return 1;
    }
    return 1;
  }

  if (wait_for_esc()) {
    printf("%s: wait_for_esc error\n", __func__);
    return 1;
  }

  if (vg_exit()) {
    printf("%s: vg_exit error\n", __func__);
    return 1;
  }

  return 0;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  if (!vg_init(mode)) {
    printf("%s: vg_init error\n", __func__);
    return 1;
  }

  if (vc_draw_pattern(mode, no_rectangles, vc_normalize_color(first), step)) {
    printf("%s: vc_draw_pattern error\n", __func__);
    if (vg_exit()) {
      printf("%s: vg_exit error\n", __func__);
      return 1;
    }
    return 1;
  }

  if (wait_for_esc()) {
    printf("%s: wait_for_esc error\n", __func__);
    return 1;
  }

  if (vg_exit()) {
    printf("%s: vg_exit error\n", __func__);
    return 1;
  }

  return 0;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  if (!vg_init(0x105)) {
    printf("%s: vg_init error\n", __func__);
    return 1;
  }

  xpm_image_t image;

  if (!xpm_load(xpm, XPM_INDEXED, &image)) {
    printf("%s: xpm_load error\n", __func__);
    return 1;
  }

  if (vc_draw_pixmap(x, y, &image)) {
    printf("%s: vc_draw_pixmap error\n", __func__);
    if (vg_exit()) {
      printf("%s: vg_exit error\n", __func__);
      return 1;
    }
    return 1;
  }

  if (wait_for_esc()) {
    printf("%s: wait_for_esc error\n", __func__);
    return 1;
  }

  if (vg_exit()) {
    printf("%s: vg_exit error\n", __func__);
    return 1;
  }

  return 0;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf, int16_t speed, uint8_t fr_rate) {
  if (!vg_init(0x105)) {
    printf("%s: vg_init error\n", __func__);
    return 1;
  }

  xpm_image_t image;

  if (!xpm_load(xpm, XPM_INDEXED, &image)) {
    printf("%s: xpm_load error\n", __func__);
    return 1;
  }

  uint16_t x = xi;
  uint16_t y = yi;
  uint16_t displacement = speed > 0 ? speed : 1;
  uint8_t fps = speed > 0 ? fr_rate : fr_rate/(-speed);

  if (vc_draw_pixmap(x, y, &image)) {
    printf("%s: vc_draw_pixmap error\n", __func__);
    if (vg_exit()) {
      printf("%s: vg_exit error\n", __func__);
      return 1;
    }
    return 1;
  }

  uint8_t timer_irq_set;
  uint8_t kbd_irq_set;

  if (timer_subscribe_int(&timer_irq_set)) {
    printf("%s: timer_subscribe_int error\n", __func__);
    return 1;
  }

	if (keyboard_subscribe_int(&kbd_irq_set)) {
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
          if (msg.m_notify.interrupts & BIT(timer_irq_set)) {
            timer_int_handler();
            if (x != xf || y != yf) {
              if ((fps * counter) % 60 == 0) {
                if (vc_clean(x, y, x + image.width, y + image.height)) {
                  printf("%s: vc_clean error\n", __func__);
                  return 1;
                }
                if (xi == xf)
                  y += displacement;
                else if (yi == yf)
                  x += displacement;
                if (x > xf || y > yf) {
                  x = xf;
                  y = yf;
                }
                if (vc_draw_pixmap(x, y, &image)) {
                  printf("%s: vc_draw_pixmap error\n", __func__);
                    if (vg_exit()) {
                      printf("%s: vg_exit error\n", __func__);
                      return 1;
                    }
                  return 1;
                }
              }
            }
          }

          if (msg.m_notify.interrupts & BIT(kbd_irq_set)) { /* subscribed interrupt */
						/* process it */
            kbc_ih();
            if (code.size > 0) {
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

  if (timer_unsubscribe_int()) {
		printf("%s: timer_unsubscribe_int error\n", __func__);
		return 1;
  }

  if (vg_exit()) {
    printf("%s: vg_exit error\n", __func__);
    return 1;
  }

  return 0;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
