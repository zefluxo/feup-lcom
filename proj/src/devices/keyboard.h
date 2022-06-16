#ifndef _KBD_H_
#define _KBD_H_

#include <lcom/lcf.h>
#include <stdint.h>
#include <minix/sysutil.h>

#include "i8042_kbd.h"

extern char keys[0x90];
extern uint8_t scan_code[2];
extern int kbd_i;
extern bool kbd_ih_flag;

#define DELAY_US 20000 // Tick delay

/* Error return values */
#define PARITY_ERR   1
#define TIME_OUT_ERR 2
#define IBF_FULL     3
#define AUX_DATA     4

/**
 * @brief Subscribes KBC interrupts
 * 
 * @return Returns 0 upon success and non-zero otherwise  
 */
int (kbd_subscribe_int) (uint8_t* bit_no);

/**
 * @brief Unsubscribes KBC interrupts
 * 
 * @brief Returns 0 upon success and non-zero otherwise  
 */
int (kbd_unsubscribe_int) ();

/**
 * @brief Checks status of the STATUS_REG
 * 
 * @return Returns 0 no problems detected and one of the error return values otherwise
 */
int (check_status) (uint8_t st);

/**
 * @brief Reads the status register 
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int (kbd_get_status) (uint8_t* st);

/**
 * @brief Reads the status output buffer 
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int (kbd_read_out_buffer) (uint8_t* output);

/**
 * @brief 
 * 
 */
int (kbd_reenable_ints) ();

/**
 * @brief Writes a command byte to the KBC command register
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int (kbd_write_cmdb) (int port, uint8_t cmdb);

/**
 * @brief Reads a command byte from the KBC command register
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int (kbd_read_ret_cmdb) (uint8_t* data);

/**
 * @brief Handles keyboard interrupts reading the status register and output buffer and handling errors 
 */
void (kbd_ih) ();

#endif /*_KBD_H_*/
