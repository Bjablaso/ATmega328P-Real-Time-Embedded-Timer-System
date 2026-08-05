/* delay.h
 * Millisecond delay interface for SER486 Assignment 5
 */

#ifndef DELAY_H
#define DELAY_H

/* Initialize delay system (configures Timer0) */
void delay_init(void);

/* Optional: get current millisecond tick */
unsigned long delay_get(unsigned int id);

/* Set a delay instance (id from 1..N) for milliseconds */
void delay_set(unsigned int id, unsigned long ms);

/* Return non-zero if delay instance is done */
int delay_isdone(unsigned int id);

#endif /* DELAY_H */
