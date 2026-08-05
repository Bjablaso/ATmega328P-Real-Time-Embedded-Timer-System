/* led.c
 * LED finite state machine for Morse-like blink pattern
 * Author: Brandon
 * SER486 Assignment 5
 */

#include <avr/io.h>
#include "led.h"
#include "delay.h"

/* We'll use PORTB5 (Arduino onboard LED) as output */
#define LED_DDR DDRB
#define LED_PORT PORTB
#define LED_PIN 5

/* We use pattern : "--- -*- " for "OK"but use simplified pattern */
static const char pattern[] = "--- -*- ";
static volatile unsigned int pat_idx = 0;
static volatile unsigned int state = 0; /* 0=idle,1=on,2=off */

void led_init(void) {
    LED_DDR |= (1 << LED_PIN);
    LED_PORT &= ~(1 << LED_PIN);
    pat_idx = 0;
    state = 0;
}

void led_update(void) {
    /* simple non-blocking FSM driven by being called in main loop */
    char c = pattern[pat_idx];
    if (c == '\0') pat_idx = 0;
    c = pattern[pat_idx];

    if (state == 0) {
        /* decide on duration */
        if (c == ' ') {
            /* inter-letter gap */
            delay_set(2, 300);
            state = 2;
        } else if (c == '-') {
            /* dash: long on */
            LED_PORT |= (1 << LED_PIN);
            delay_set(2, 300);
            state = 1;
        } else if (c == '.') {
            LED_PORT |= (1 << LED_PIN);
            delay_set(2, 100);
            state = 1;
        } else {
            /* unknown, advance */
            pat_idx++;
        }
    } else if (state == 1) {
        /* we are ON, wait for timer then turn off */
        if (delay_isdone(2)) {
            LED_PORT &= ~(1 << LED_PIN);
            delay_set(2, 100); /* intra-char gap */
            state = 2;
            pat_idx++;
        }
    } else if (state == 2) {
        /* OFF waiting */
        if (delay_isdone(2)) {
            state = 0;
        }
    }
}
