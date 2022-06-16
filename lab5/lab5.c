// IMPORTANT: you must include the following line in all your C files
#include <lcom/lcf.h>
#include <lcom/lab5.h>
#include <stdint.h>
#include <stdio.h>

// Any header files included below this line should have been created by you

#include "defines.h"
#include "video.h"
#include "pixmap.h"
#include "keyboard.h"

#include "keyboard.c"
#include "utils.c"

extern uint8_t scan_code[2];
extern int i;

int main(int argc, char *argv[]) {
  // sets the language of LCF messages (can be either EN-US or PT-PT)
  lcf_set_language("EN-US");

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
  
  if (change_mode(mode) != 0) return EXIT_FAILURE;
  sleep(delay);
  if (vg_exit() != 0) return EXIT_FAILURE;

  return 0;

}

int(video_test_rectangle)(uint16_t mode, uint16_t x, uint16_t y,
                          uint16_t width, uint16_t height, uint32_t color) {

  if (map_vm(mode) != 0) {
    return EXIT_FAILURE; 
  }
  
  if (change_mode(mode) != 0) {
    return EXIT_FAILURE;
  }

  vg_draw_rectangle(x, y, width, height, color);

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
            
            i = 0;

          }
          break;
        }

        default: break;
      }
    }
  }

  kbd_unsubscribe_int();

  vg_exit();
  
  return EXIT_SUCCESS;
}

int(video_test_pattern)(uint16_t mode, uint8_t no_rectangles, uint32_t first, uint8_t step) {
  /* To be completed */
  printf("%s(0x%03x, %u, 0x%08x, %d): under construction\n", __func__,
         mode, no_rectangles, first, step);

  return 1;
}

int(video_test_xpm)(xpm_map_t xpm, uint16_t x, uint16_t y) {
  
  int r, a;

  if ((r = map_vm(0x105)) != 0) {
    return EXIT_FAILURE; 
  }
  
  if ((a = change_mode(0x105)) != 0) {
    return EXIT_FAILURE;
  }
  
  xpm_image_t img;
  xpm_load(xpm, XPM_INDEXED, &img);
  
  draw_xpm(img, x, y);

  sleep(4);

  vg_exit();

  return 1;
}

int(video_test_move)(xpm_map_t xpm, uint16_t xi, uint16_t yi, uint16_t xf, uint16_t yf,
                     int16_t speed, uint8_t fr_rate) {
  /* To be completed */
  printf("%s(%8p, %u, %u, %u, %u, %d, %u): under construction\n",
         __func__, xpm, xi, yi, xf, yf, speed, fr_rate);

  return 1;
}

int(video_test_controller)() {
  /* To be completed */
  printf("%s(): under construction\n", __func__);

  return 1;
}
