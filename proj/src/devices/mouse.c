#include "mouse.h"

int mouse_hook_id = 12;

struct packet pp;
int mouse_i;
bool mouse_ready = false;

int(mouse_subscribe_int)(uint8_t *bit_no) {
  *bit_no = mouse_hook_id;
  return sys_irqsetpolicy(KBD_AUX_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &mouse_hook_id);
}

int(mouse_unsubscribe_int)() {
  return sys_irqrmpolicy(&mouse_hook_id);
}

int(mouse_get_status)(uint8_t *st) {
  return util_sys_inb(STATUS_REG, st);
}

int(mouse_write_cmd)(uint8_t cmdb) {

  int timeout = 0;
  uint8_t st;

  while (timeout < 3) {

    if (mouse_get_status(&st) != 0) {
      fprintf(stderr, "Error getting status while issuing command!\n");
      return -1;
    }

    if (!(st & IBF)) {
      sys_outb(MOUSE_CMD_REG, WRITE_AUX);
    }


    if (mouse_get_status(&st) != 0) {
      fprintf(stderr, "Error getting status while issuing command!\n");
      return -1;
    }

    if (!(st & IBF)) {
      sys_outb(MOUSE_ARGS, cmdb);
    }

    tickdelay(micros_to_ticks(DELAY_US2));

    uint8_t ack_byte;
    util_sys_inb(OUT_BUF, &ack_byte);

    if (ack_byte == MOUSE_OK) return 0;

    timeout++;
  }

  return -1;
}

int(mouse_read_buffer)(uint8_t port, uint8_t *output) {

  int timeout = 0;
  uint8_t st;

  while (timeout < 3) {

    if (mouse_get_status(&st) != 0) {
      fprintf(stderr, "Error getting status when reading from buffer!\n");
      return -1;
    }

    if ((st & (OBF | AUX)) && !((st & (PARITY | TIME_OUT)))) {

      if (util_sys_inb(port, output) != 0) {
        fprintf(stderr, "Error reading from buffer!\n");
        return -1;
      }

      return 0;
    }
    else return -1;

    tickdelay(micros_to_ticks(DELAY_US2));
    timeout++;
  }

  return -1;
}

int (_mouse_enable_data_reporting)() {
  return mouse_write_cmd(ENBL_DATA_REP);
}

int(mouse_disable_data_reporting)() {
  return mouse_write_cmd(DIS_DATA_REP);
}

void(mouse_ih)() {

  uint8_t output, st;
  mouse_get_status(&st);

  if (st & OBF && !(st & (PARITY | TIME_OUT))) {

    if (mouse_read_buffer(OUT_BUF, &output) != 0) {
      fprintf(stderr, "Error reading from buffer in mouse!\n");
      return;
    }

    pp.bytes[mouse_i] = output;
    
    if (mouse_i == 0 && !(output & FIRST_BYTE)) {
      while (mouse_read_buffer(OUT_BUF, &output) == 0) {
        continue;
      }
      return;
    }

    switch (mouse_i) {
      case 0:
        pp.lb = output & BIT(0);
        pp.rb = output & BIT(1);
        pp.mb = output & BIT(2);

        pp.x_ov = output & BIT(6);
        pp.y_ov = output & BIT(7);
        break;

      case 1:
        pp.delta_x = output;
        if (pp.bytes[0] & BIT(4)) pp.delta_x |= 0xFF00;
        break;
        
      case 2:
        pp.delta_y = output;
        if (pp.bytes[0] & BIT(5)) pp.delta_y |= 0xFF00;
        break;
    }

    mouse_i++;

    if (mouse_i == 3) {
      mouse_ready = true;
      mouse_i = 0;
    }

  }
}
