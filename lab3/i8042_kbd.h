#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/* I/O Ports */
#define KBD_IRQ       1             // keyboard interrupt line
#define OUT_BUF       0x60          // output buffer port
#define KBC_ARGS      0x60          // same as output buffer, used for sending KBC command arguments
#define STATUS_REG    0x64          // status register port
#define KBC_CMD_REG   0x64          // same as status register, but used for issuing KBC commands

/* Bit masks */
#define PARITY        BIT(7)        // bit mask to check for parity error
#define TIME_OUT      BIT(6)        // bit mask to check for timeout error
#define AUX           BIT(5)        // bit mask to check if we're receiving mouse data
#define IBF           BIT(1)        // bit mask to check if input buffer is full
#define OBF           BIT(0)        // bit mask to check if output buffer is full
#define KBC_INT       BIT(0)        // bit mask to check if keyboard interrupts are enabled
#define IS_BREAK      BIT(7)        // bit mask to check if a scancode is a breakcode

/* Constants */
#define TWO_BYTE_SC   0xE0          // value to check if we are dealing with a 2 byte scan code
#define ESC_MAKE      0x01          // makecode for ESC
#define ESC_BREAK     0x81          // breakcode for ESC
#define KBC_OK        0x55          // code for valid keyboard controller
#define KBC_ERR       0xFC          // code for invalid keyboard controller

/* KBC Commands */
#define READ_CMDB     0x20          // read command byte
#define WRITE_CMDB    0x60          // write command byte
#define KBC_CHK       0xAA          // check keyboard controller; returns KBC_OK if ok, else KBC_ERR
#define KBI_CHK       0xAB          // check keyboard interface; returns 0 if OK
#define KBI_DIS       0xAD          // disable keyboard interface
#define KBI_ENA       0xAE          // enable keyboard interface

#endif /*_LCOM_I8042_H_*/
