#ifndef _LCOM_RTC_H_
#define _LCOM_RTC_H_

#define WAIT              244

#define RTC_IRQ           8         // RTC interrupt line
#define RTC_ADDR_REG      0x70      // RTC address register (written to)
#define RTC_DATA_REG      0x71      // RTC data register (written/read to/from)

#define RTC_SECS          0x00      // Seconds register
#define RTC_SECS_ALARM    0x01      // Seconds alarm register
#define RTC_MINS          0x02      // Minutes register
#define RTC_MINS_ALARM    0x03      // Minutes alarm register
#define RTC_HOURS         0x04      // Hours register
#define RTC_HOURS_ALARM   0x05      // Hours alarm register
#define RTC_WEEK_DAY      0x06      // Day of the week register
#define RTC_MONTH_DAY     0x07      // Day of the month register
#define RTC_MONTH         0x08      // Month register
#define RTC_YEAR          0x09      // Year register

#define RTC_REG_A         0x0A      // Register A
#define RTC_REG_B         0x0B      // Register B
#define RTC_REG_C         0x0C      // Register C
#define RTC_REG_D         0x0D      // Register D

/* Register A bit masks */
#define RTC_UIP           BIT(7)    // Bit mask to check for Update In Progress

/* Register B bit masks */
#define RTC_SET           BIT(7)    // Bit mask to inhibit updates of time/date registers

#define RTC_PIE           BIT(6)    // Bit mask to enable Periodic interrupts
#define RTC_AIE           BIT(5)    // Bit mask to enable Alarm interrupts
#define RTC_UIE           BIT(4)    // Bit mask to enable Update-ended interrupts

#define RTC_DM            BIT(2)    // Bit mask to set time, alarm and date registers in binary
#define RTC_TW_FO         BIT(1)    // Bit mask to set hours range to 0-23
#define RTC_DST           BIT(0)    // Bit mask to enable daylight savings

/* Register C bit masks */

// IRQF = ((PF == PIE == 1) || (AF == AIE == 1) || (UF == UIE == 1))
#define RTC_IRQF          BIT(7)    // Bit mask to check for an interrupt

#define RTC_PF            BIT(6)    // Periodic flag
#define RTC_AF            BIT(5)    // Alarm flag
#define RTC_UF            BIT(4)    // Update-ended flag

/* Register D bit masks */
#define RTC_VRT           BIT(7)    // Bit mask to check if the internal lithium battery has power

#endif /*_LCOM_RTC_H_*/
