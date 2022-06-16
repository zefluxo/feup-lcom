#pragma once

#include <lcom/lcf.h>
#include <stdint.h>

#include "rtc_defines.h"

typedef struct {
  uint16_t day;
  uint16_t month;
  uint16_t year;
} Date;

/**
 * @brief Write to the RTC address register
 * 
 * @param data The data to be written
 */
int (rtc_write_addr) (uint8_t addr);

/**
 * @brief Read from the RTC data register
 * 
 * @param data The data to be read
 */
int (rtc_read_data) (uint8_t* data);

/**
 * @brief Write data to the RTC address register
 * 
 * @param data The data to be written 
 */
int (rtc_write_data) (uint8_t data);

/**
 * @brief Creates a Date object like struct with information of the current day, month and year
 * 
 * @return A Date object like struct with day, month and year information
 */
Date (rtc_read_time) ();
