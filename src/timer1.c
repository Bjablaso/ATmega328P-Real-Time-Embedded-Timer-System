/* timer1.c
 * Timer implementation to provide a 1 second tick and simple RTC
 * Author: Brandon Jablasone
 * SER486 Project 5
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdio.h>
#include "timer1.h"

static volatile uint8_t rtc_sec = 0;
static volatile uint8_t rtc_min = 0;
static volatile uint8_t rtc_hour = 0;
static volatile uint8_t rtc_day = 1;
static volatile uint8_t rtc_month = 1;
static volatile uint16_t rtc_year = 2019;
static volatile unsigned long timer1_ticks = 0;

void rtc_set(uint8_t month, uint8_t day, uint16_t year, uint8_t hour, uint8_t min, uint8_t sec) {
    rtc_month = month;
    rtc_day = day;
    rtc_year = year;
    rtc_hour = hour;
    rtc_min = min;
    rtc_sec = sec;
}

unsigned long timer1_get(void) {
    return timer1_ticks;
}

void timer1_clear(void) {
    timer1_ticks = 0;
}

void timer1_init(void) {
    /* Configure Timer1 CTC with prescaler 1024 for 1s tick
       16MHz / 1024 = 15625 Hz -> OCR1A = 15624 for 1 second */
    cli();
    TCCR1A = 0;
    TCCR1B = (1 << WGM12); /* CTC */
    OCR1A = 15624;
    TCCR1B |= (1 << CS12) | (1 << CS10); /* prescaler 1024 */
    TIMSK1 |= (1 << OCIE1A);
    sei();
}

ISR(TIMER1_COMPA_vect) {
    timer1_ticks++;
    /* increment RTC  */
    rtc_sec++;
    if (rtc_sec >= 60) {
        rtc_sec = 0; rtc_min++;
        if (rtc_min >= 60) {
            rtc_min = 0; rtc_hour++;
            if (rtc_hour >= 24) {
                rtc_hour = 0; rtc_day++;
                /* simple month handling */
                const uint8_t mdays[] = {31,28,31,30,31,30,31,31,30,31,30,31};
                if (rtc_day > mdays[(rtc_month-1) % 12]) {
                    rtc_day = 1; rtc_month++;
                    if (rtc_month > 12) { rtc_month = 1; rtc_year++; }
                }
            }
        }
    }
}

void rtc_get_date_string(char *buf) {
    /* Format MM/DD/YYYY hh:mm:ss\0 */
    sprintf(buf, "%02u/%02u/%04u %02u:%02u:%02u", rtc_month, rtc_day, rtc_year, rtc_hour, rtc_min, rtc_sec);
}
