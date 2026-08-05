/* rtc.h
 * RTC API (implemented in timer.c)
 */

#ifndef RTC_H
#define RTC_H

#include <stdint.h>

/* get formatted date string into buf (>=20 bytes) */
void rtc_get_date_string(char *buf);

/* set rtc date/time */
void rtc_set(uint8_t month, uint8_t day, uint16_t year, uint8_t hour, uint8_t min, uint8_t sec);

#endif /* RTC_H */
