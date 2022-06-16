#include <lcom/lcf.h>
#include <lcom/lab4.h>
#include <stdint.h>

#include "i8042_mouse.h"

#define DELAY_US2 25000 // Tick delay

extern struct packet pp;
extern int mouse_i;
extern bool mouse_ready;

/**
 * @brief Subscribes mouse input interrupts
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int (mouse_subscribe_int) (uint8_t* bit_no);

/**
 * @brief Unsubscribes mouse input interrupts
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int (mouse_unsubscribe_int)();

/**
 * @brief Enables the mouse data reporting functionality
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int (_mouse_enable_data_reporting)();

/**
 * @brief Disables the mouse data reporting functionality
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int (mouse_disable_data_reporting)();

/**
 * @brief Enables mouse stream mode
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int (mouse_enable_stream_mode)();

/**
 * @brief Reads mouse status register
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int (mouse_get_status) (uint8_t* st);

/**
 * @brief Reads mouse output buffer
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int (mouse_read_buffer) (uint8_t port, uint8_t* output);

/**
 * @brief Writes a command byte to the mouse command register
 * 
 * @return Returns 0 upon success and non-zero otherwise
 */
int (mouse_write_cmd) (uint8_t cmdb);

/**
 * @brief Handles mouse interrupt, processing errors and building packets of mouse information  
 * 
 */
void (mouse_ih)();
