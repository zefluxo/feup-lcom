#ifndef _LCOM_I8042_H_
#define _LCOM_I8042_H_

#include <lcom/lcf.h>

/* I/O Ports */
#define OUT_BUF       0x60          // output buffer port
#define STATUS_REG    0x64          // status register port
#define MOUSE_ARGS    0x60          // same as output buffer, but used for sending command arguments
#define MOUSE_CMD_REG 0x64          // same as status register, but used for issuing commands

/* Bit masks */
#define PARITY        BIT(7)        // bit mask to check for parity error
#define TIME_OUT      BIT(6)        // bit mask to check for timeout error
#define AUX           BIT(5)        // bit mask, 1 if mouse data, 0 if keyboard data
#define IBF           BIT(1)        // bit mask to check if input buffer is full
#define OBF           BIT(0)        // bit mask to check if output buffer is full

#define DIS2          BIT(5)        // bit set to 1 for disabling mouse in command byte
#define DIS1          BIT(4)        // bit set to 1 for disabling kbd in command byte
#define INT2          BIT(1)        // bit set to 1 to enable OBF interrupts from mouse
#define INT1          BIT(0)        // bit set to 1 to enable OBF interrupts from kbd

#define FIRST_BYTE    BIT(3)        // bit mask to check if we are receiving a packet's first byte

/* Constants */
#define MOUSE_OK      0xFA          // signals a mouse command had no issues
#define MOUSE_NACK    0xFE          // signals invalid byte
#define MOUSE_ERR     0xFC          // signals second consecutive invalid byte

/* KBC Commands */
#define READ_CMDB     0x20          // read command byte
#define WRITE_CMDB    0x60          // write command byte
#define MOUSE_DIS     0xA7          // disable mouse
#define MOUSE_ENBL    0xA8          // enable mouse
#define CHK_MOUSE     0xA9          // check mouse interface
#define WRITE_AUX     0xD4          // write byte to mouse

/* Mouse Commands */
#define MOUSE_RESET   0xFF          // resets the mouse
#define MOUSE_RESEND  0xFE          // resend byte (used for communication errors)
#define MOUSE_DEFAULT 0xF6          // set default mouse settings
#define DIS_DATA_REP  0xF5          // disables mouse data reporting
#define ENBL_DATA_REP 0xF4          // enables mouse data reporting
#define SET_SAMPLE    0xF3          // set sample rate
#define SET_REMOTE    0xF0          // set mouse to remote mode
#define READ_DATA     0xEB          // request a packet from the mouse (remote mode only)
#define SET_STREAM    0xEA          // set mouse to stream mode
#define MOUSE_CFG     0xE9          // get mouse configuration

#endif /*_LCOM_I8042_H_*/
