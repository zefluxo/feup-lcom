#include <lcom/lab3.h>
#include <lcom/lcf.h>

#include "i8042_kbd.h"
#include "keyboard.h"
#include "timer.c" // definitely a better way to do this, i don't know how

uint8_t scan_code[2];
int i = 0;
bool ih_flag;

extern int counter;
extern int timer_counter;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

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
  uint8_t bit_no;
  kbd_subscribe_int(&bit_no);

  uint32_t irq_set = BIT(bit_no);

  message msg;
  int ipc_status;

  while (scan_code[i] != ESC_BREAK) {
    
    int r;
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != OK) {
      printf("driver_receive failed with: %d", r);
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {

        case HARDWARE: {
          if (msg.m_notify.interrupts & irq_set) {

            kbc_ih();

            if (scan_code[i] == TWO_BYTE_SC) {
              i++;
              continue;
            }
            
            kbd_print_scancode(ih_flag, (i+1), scan_code);
            i = 0;

          }

          break;
        }

        default: break;
      }
    }
  }

  kbd_unsubscribe_int();
  kbd_print_no_sysinb(counter);

  return 0;
}

int(kbd_test_poll)() {

  bool is_make;

  while (scan_code[i] != ESC_BREAK) {

    uint8_t st;
    if (kbd_get_status(&st) != 0) {
      fprintf(stderr, "Error getting status from status register while polling!\n");
      return -1;
    }

    if (st & OBF && (check_status(st) == 0)) {
      
      uint8_t output;
      if (kbd_read_out_buffer(&output) != 0) {
        fprintf(stderr, "Error reading output from buffer while polling!\n");
        return -1;
      }

      scan_code[i] = output;

      if (output == TWO_BYTE_SC) {
        i++;
        continue;
      }

      is_make = (output & IS_BREAK) ? false: true;

      kbd_print_scancode(is_make, (i+1), scan_code);
      i = 0;

    }

  }

  if (kbd_reenable_ints() != 0) {
    fprintf(stderr, "Error reenabling interrupts after polling!\n");
    return -1;
  }

  kbd_print_no_sysinb(counter);

  return 0;
}

int(kbd_test_timed_scan)(uint8_t n) {
  uint8_t kbd_bit_no;
  kbd_subscribe_int(&kbd_bit_no);

  uint8_t timer_bit_no;
  timer_subscribe_int(&timer_bit_no);


  uint32_t kbd_irq_set = BIT(kbd_bit_no);
  uint32_t timer_irq_set = BIT(timer_bit_no);

  message msg;
  int ipc_status;

  while (scan_code[i] != ESC_BREAK && (timer_counter/60.0) < n) {
    
    int r;
    if ((r = driver_receive(ANY, &msg, &ipc_status)) != OK) {
      printf("driver_receive failed with: %d", r);
    }

    if (is_ipc_notify(ipc_status)) {
      switch (_ENDPOINT_P(msg.m_source)) {

        case HARDWARE: {
          if (msg.m_notify.interrupts & kbd_irq_set) { // keyboard interrupt

            kbc_ih();

            if (scan_code[i] == TWO_BYTE_SC) {
              i++;
              continue;
            }
            
            kbd_print_scancode(ih_flag, (i+1), scan_code);
            i = 0;
            timer_counter = 0;

          }

          if (msg.m_notify.interrupts & timer_irq_set) { // timer interrupt
            
            timer_int_handler();
            
          }

          break;
        }

        default: break;
      }
    }
  }

  kbd_unsubscribe_int();
  timer_unsubscribe_int();
  kbd_print_no_sysinb(counter);

  return 0;
}


void(kbc_ih)(void) {

  uint8_t output;
  kbd_read_out_buffer(&output);

  uint8_t st;
  kbd_get_status(&st);

  if (check_status(st) == 0) {

    scan_code[i] = output;

    if (output != TWO_BYTE_SC) {
      if (output & IS_BREAK) {
        ih_flag = false;
      } else {
        ih_flag = true;
      }
    }

  }
}
