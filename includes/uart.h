/* uart.h
 * UART interface for SER486 Assignment 1
 */

#ifndef UART_H
#define UART_H

void uart_init(void);                   /* initialize uart */
void uart_writechar(char ch);           /* write single character */
void uart_writestr(const char *str);    /* write string */
void uart_writehex8(unsigned char num); /* write 8-bit hex */
void uart_writehex16(unsigned int num); /* write 16-bit hex */
void uart_writedec32(signed long num);  /* write 32-bit decimal */

#endif /* UART_H */
