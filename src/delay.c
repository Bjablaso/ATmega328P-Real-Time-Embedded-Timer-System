/* delay.c
 * Millisecond delay implementation using AVR Timer0 CTC mode
 * Author: Brandon Jablasone
 * SER486 Assignment 5
 */

#include <avr/io.h>
#include <avr/interrupt.h>
#include <stdint.h>

/* Support up to 4 delay instances */
#define DELAY_INSTANCES 4

static volatile uint32_t g_ms = 0;
static volatile uint32_t g_target[DELAY_INSTANCES];

void delay_init(void) {
    /* We configure the  Timer with  a prescaler of  64 that generate  a 1ms interrupts
       16MHz / 64 = 250kHz -> OCR0A = 249 produces 1000Hz -> 1ms */
    TCCR0A = (1 << WGM01); /* CTC */
    OCR0A = 249;
    TCCR0B = (1 << CS01) | (1 << CS00); /* prescaler 64 */
    TIMSK0 |= (1 << OCIE0A); /* A interrupt */

    for (int i = 0; i < DELAY_INSTANCES; ++i) g_target[i] = 0;
    sei();
}

void delay_set(unsigned int id, unsigned long ms) {
    if (id == 0 || id > DELAY_INSTANCES) return;
    uint32_t t = g_ms + ms;
    g_target[id - 1] = t;
}

int delay_isdone(unsigned int id) {
    if (id == 0 || id > DELAY_INSTANCES) return 1;
    return (int)(g_ms >= g_target[id - 1]);
}

unsigned long delay_get(unsigned int id) {
    (void)id;
    return g_ms;
}

ISR(TIMER0_COMPA_vect) {
    ++g_ms;
}
