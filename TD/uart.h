#ifndef UART_H
#define UART_H
#include <stdint.h>
#include <stddef.h>
/* This file provides a set of functions to send values to and read information from
the serial port. */

/* Initialization of all the registers related to the serial port USART1 */
void uart_init(int baudrate);
/* Read a 8bit value from the serial port */
uint8_t uart_getchar();
void uart_putchar(uint8_t c);
/* Print a sequence of characters through the serial port followed by a 
new line character '\n'. It is equivalent to puts*/
void uart_puts(const uint8_t *s);
/* Read a sequence of 8bits words from the serial port. It stops when a new line character '\n'
is read or when size-1 values have been read. Equivalent to fgets */
void uart_gets(uint8_t *s, size_t size);
/* Calculate the sum of a stream of 8bit numbers read from the serial port. */
uint32_t sum_of_hex();

#endif