/* timer1.h
 * Timer1 interface
 */

#ifndef TIMER1_H
#define TIMER1_H

#include <stdint.h>

/* initialize Timer1 for 1 second tick */
void timer1_init(void);

/* optional helpers (not required) */
unsigned long timer1_get(void);
void timer1_clear(void);

#endif /* TIMER1_H */
