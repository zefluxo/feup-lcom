#include "rtc.h"

int(rtc_write_addr)(uint8_t addr) {
  return sys_outb(RTC_ADDR_REG, addr);
}

int(rtc_read_data)(uint8_t *data) {
  return util_sys_inb(RTC_DATA_REG, data);
}

int(rtc_write_data)(uint8_t data) {
  return sys_outb(RTC_DATA_REG, data);
}

Date (rtc_read_time) () {

  uint8_t reg;
  rtc_write_addr(RTC_REG_B);
  rtc_read_data(&reg);

  reg |= RTC_DM;

  rtc_write_addr(RTC_REG_B);
  rtc_write_data(reg);

  rtc_write_addr(RTC_REG_A);
  rtc_read_data(&reg);

  while (!reg & RTC_UIP) {
    rtc_write_addr(RTC_REG_A);
    rtc_read_data(&reg);
  }

  tickdelay(micros_to_ticks(WAIT));

  uint8_t time[3] = {0, 0, 0};
  uint8_t regs[3] = {RTC_MONTH_DAY, RTC_MONTH, RTC_YEAR};

  for (int i = 0; i < 3; i++) {
    rtc_write_addr(regs[i]);
    rtc_read_data(&time[i]);
  }

  Date date = {time[0], time[1], time[2]};
  return date;
}
