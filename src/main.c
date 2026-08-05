/*
 * main.c
 * SER486 Project 5 - Brandon Jablasone
 * Demonstrates timer-based delays, Timer RTC, and LED FSM
 */

#include "delay.h"
#include "led.h"
#include "timer1.h"
#include "rtc.h"
#include "uart.h"

int main(void) {
    /* initialize subsystems */
    uart_init();
    delay_init();
    timer1_init();
    led_init();
    rtc_set(1,1,2019,0,0,0);

    uart_writestr("SER 486 Project 5 - Brandon Jablasone\n\r");

    /* profile led_update */
    signed long c1 = 0;
    delay_set(1, 10000);
    while (!delay_isdone(1)) { c1++; }

    signed long c2 = 0;
    delay_set(1, 10000);
    while (!delay_isdone(1)) { led_update(); c2++; }

    uart_writedec32(c1); uart_writestr(" ");
    uart_writedec32(c2); uart_writestr("\r\n");

    /* main loop */
    delay_set(1, 500);
    char buf[32];
    while (1) {
        led_update();

        if (delay_isdone(1)) {
            delay_set(1, 500);
            rtc_get_date_string(buf);
            uart_writestr(buf);
            uart_writestr("\r");
        }
    }

    return 0;
}