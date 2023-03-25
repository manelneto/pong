#include <lcom/lcf.h>
#include "mouse.h"
#include "kbc.h"

#include "i8042.h"

struct packet mouse_packet;
int32_t mouse_hook_id = MOUSE_IRQ;
uint8_t packet_index = 0;

int (mouse_subscribe_int)(uint8_t *bit_no) {
	*bit_no = mouse_hook_id;

	if (sys_irqsetpolicy(MOUSE_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id)) {
		printf("%s: sys_irqsetpolicy error\n", __func__);
		return 1;
	}

	return 0;
}

int (mouse_unsubscribe_int)() {
	if (sys_irqrmpolicy(&mouse_hook_id)) {
		printf("%s: sys_irqrmpolicy error\n", __func__);
		return 1;
	}
	return 0;
}

int mouse_read_packet_byte() {
  uint8_t output;
  if (kbc_read_output(&output)) {
    printf("%s: kbc_read_output error\n", __func__);
    return 1;
  }

  if (packet_index == 0 && !(output & MOUSE_BYTE1))
    return 1;

  mouse_packet.bytes[packet_index] = output;

  if (packet_index == 1)
    mouse_packet.delta_x |= output;
  else if (packet_index == 2) {
    mouse_packet.delta_y |= output;

    uint8_t first_byte = mouse_packet.bytes[0];

    mouse_packet.lb = (bool) (first_byte & MOUSE_LB);
    mouse_packet.rb = (bool) (first_byte & MOUSE_RB);
    mouse_packet.mb = (bool) (first_byte & MOUSE_MB);

    if (first_byte & MOUSE_MSB_X_DELTA)
      mouse_packet.delta_x |= MOUSE_SET_MSB;
    
    if (first_byte & MOUSE_MSB_Y_DELTA)
      mouse_packet.delta_y |= MOUSE_SET_MSB;
    
    mouse_packet.x_ov = (bool) (first_byte & MOUSE_X_OVFL);
    mouse_packet.y_ov = (bool) (first_byte & MOUSE_Y_OVFL);
  }

  packet_index++;

  return 0;
}

void (mouse_ih)() {
  mouse_read_packet_byte();
}

int (mouse_restore)() {
  mouse_packet.bytes[0] = 0;
  mouse_packet.bytes[1] = 0;
  mouse_packet.bytes[2] = 0;
  mouse_packet.delta_x = 0;
  mouse_packet.delta_y = 0;
  packet_index = 0;
  return 0;
}

int (mouse_write_command)(uint8_t command) {
  for (int i = 0; i < KBC_MAX_ATTEMPTS; i++) {
    if (kbc_write_command(KBC_WRITE_TO_MOUSE)) {
      printf("%s: kbc_write_command error\n");
      return 1;
    }

    if (kbc_write_argument(command)) {
      printf("%s: kbc_write_argument error\n", __func__);
      return 1;
    }

    uint8_t acknowledgment_byte;
    if (kbc_read_acknowledgment_byte(&acknowledgment_byte)) {
      printf("%s: kbc_read_acknowledgment_byte error\n", __func__);
      return 1;
    }

    if (acknowledgment_byte == KBC_ACK)
      return 0;

    if (acknowledgment_byte == KBC_ERROR)
      return 1;

    tickdelay(micros_to_ticks(KBD_DELAY_US));
  }

  return 0;
}

int (mouse_data_reporting)(bool enable) {
  if (enable) {
    if (mouse_write_command(KBC_ENABLE_DATA_REPORTING)) {
      printf("%s: mouse_write_command error\n");
      return 1;
    }
  } else {
    if (mouse_write_command(KBC_DISABLE_DATA_REPORTING)) {
      printf("%s: mouse_write_command error\n");
      return 1;
    }
  }
  return 0;
}

struct mouse_ev* (mouse_detect_event_our)(struct packet* pp) {
  static struct packet previous_pp;
  static struct mouse_ev event;

  event.delta_x = pp->delta_x;
  event.delta_y = pp->delta_y;

  if (pp->lb && !pp->rb && !pp->mb && !previous_pp.lb && !previous_pp.rb && !previous_pp.mb)
    event.type = LB_PRESSED;
  
  else if (!pp->lb && !pp->rb && !pp->mb && previous_pp.lb && !previous_pp.rb && !previous_pp.mb)
    event.type = LB_RELEASED;

  else if (!pp->lb && pp->rb && !pp->mb && !previous_pp.lb && !previous_pp.rb && !previous_pp.mb)
    event.type = RB_PRESSED;

  else if (!pp->lb && !pp->rb && !pp->mb && !previous_pp.lb && previous_pp.rb && !previous_pp.mb)
    event.type = RB_RELEASED;

  else if (pp->lb == previous_pp.lb && pp->rb == previous_pp.rb && pp->mb == previous_pp.mb && (pp->delta_x != 0 || pp->delta_y != 0))
    event.type = MOUSE_MOV;

  else {
    event.type = BUTTON_EV;
    event.delta_x = 0;
    event.delta_y = 0;
  }

  previous_pp = *pp;

  return &event;
}

bool (mouse_check_logical_and)(struct mouse_ev *event, uint8_t x_len, uint8_t tolerance) {
  static state_t state = INITIAL; // initial state; keep state
  static int16_t x_displacement;
  static int16_t y_displacement;

  switch (state) {
    case INITIAL:
      x_displacement = 0;
      y_displacement = 0;
      if (event->type == LB_PRESSED)
        state = FIRST_LINE;
      break;

    case FIRST_LINE:
      if (event->type == MOUSE_MOV) {
        if ((event->delta_x < 0 && abs(event->delta_x) > tolerance) || (event->delta_y < 0 && abs(event->delta_y) > tolerance))
          state = INITIAL;
        else {
          x_displacement += event->delta_x;
          y_displacement += event->delta_y;
        }
      }
      else if (event->type == LB_RELEASED && x_displacement >= x_len && (float) abs(y_displacement) / (float) abs(x_displacement) > 1) {
        x_displacement = 0;
        y_displacement = 0;
        state = VERTEX;
      }
      else
        state = INITIAL;
      break;

    case VERTEX:
      if (event->type == MOUSE_MOV) {
          x_displacement += event->delta_x;
          y_displacement += event->delta_y;
          if (abs(x_displacement) > tolerance || abs(y_displacement) > tolerance)
            state = INITIAL;
      }
      else if (event->type == LB_PRESSED)
        state = FIRST_LINE;
      else if (event->type == RB_PRESSED) {
        x_displacement = 0;
        y_displacement = 0;
        state = SECOND_LINE;
      }
      else
        state = INITIAL;
      break;

    case SECOND_LINE:
      if (event->type == MOUSE_MOV) {
        if ((event->delta_x < 0 && abs(event->delta_x) > tolerance) || (event->delta_y > 0 && abs(event->delta_y) > tolerance))
          state = INITIAL;
        else {
          x_displacement += event->delta_x;
          y_displacement += event->delta_y;
        }
      }
      else if (event->type == RB_RELEASED && x_displacement >= x_len && (float) abs(y_displacement) / (float) abs(x_displacement) > 1)
        return true;
      else
        state = INITIAL;
      break;
    
    default:
      break;
  }

  return false;
}
