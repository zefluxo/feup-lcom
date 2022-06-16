#include "keyboard.h"

static int kbd_id = 1;
int counter = 0;

int(kbd_subscribe_int)(uint8_t *bit_no) {
  *bit_no = kbd_id;
  return sys_irqsetpolicy(KBD_IRQ, IRQ_REENABLE | IRQ_EXCLUSIVE, &kbd_id);
}

int(kbd_unsubscribe_int)() {
  return sys_irqrmpolicy(&kbd_id);
}

int(check_status)(uint8_t st) {

  if (st & PARITY) {
    return PARITY_ERR;
  }

  if (st & TIME_OUT) {
    return TIME_OUT_ERR;
  }

  if (st & AUX) {
    return AUX_DATA;
  }

  /* might cause issues with the lab, since we won't be writing to the input buffer
  if (st & IBF) {
      return IBF_FULL;
  }
  */

  return OK;
}

int(kbd_get_status)(uint8_t *st) {
  return util_sys_inb(STATUS_REG, st);
}

int(kbd_read_out_buffer)(uint8_t *output) {
  return util_sys_inb(OUT_BUF, output);
}

int(kbd_write_cmdb)(int port, uint8_t cmdb) {

  int timeout = 0;
  uint8_t st;

  while (timeout < 3) {

    if (kbd_get_status(&st) != 0) {
      fprintf(stderr, "Error getting status while issuing command!\n");
      return -1;
    }

    if ((st & IBF) == 0) {
      sys_outb(port, cmdb);
      return 0;
    }

    tickdelay(micros_to_ticks(DELAY_US));
    timeout++;
  }

  return -1;
}

int(kbd_read_ret_cmdb)(uint8_t *data) {

  int timeout = 0;
  uint8_t st;

  while (timeout < 3) {

    if (kbd_get_status(&st) != 0) {
      fprintf(stderr, "Error getting status when reading command byte return value!\n");
      return -1;
    }

    if (st & OBF && !(st & (PARITY | TIME_OUT | AUX))) {

      if (kbd_read_out_buffer(data) != 0) {
        fprintf(stderr, "Error reading KBC command byte return value from output buffer!\n");
        return -1;
      }

      return 0;
    
    } else return -1;

    tickdelay(micros_to_ticks(DELAY_US));
    timeout++;

  }
  
  return 0;
}

int(kbd_reenable_ints)() {

  uint8_t output;

  if (kbd_write_cmdb(KBC_CMD_REG, READ_CMDB) != 0) {
    fprintf(stderr, "Error writing command byte while reenabling interrupts!\n");
    return -1;
  }

  if (kbd_read_ret_cmdb(&output) != 0) {
    fprintf(stderr, "Error reading return command byte!\n");
    return -1;
  }

  output |= KBC_INT;

  if (kbd_write_cmdb(KBC_CMD_REG, WRITE_CMDB) != 0) {
    fprintf(stderr, "Error writing command byte while reenabling interrupts!\n");
    return -1;
  }

  if (kbd_write_cmdb(KBC_ARGS, output) != 0) {
    fprintf(stderr, "Error writing command byte arguments to input buffer!\n");
    return -1;
  }

  return 0;
}
