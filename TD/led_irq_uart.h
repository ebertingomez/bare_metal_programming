#ifndef LED_IRQ_UART_H

#define LED_IRQ_UART_H
#include "uart.h"
#include "matrix.h"
#include "irq.h"

/* Pointer to the  beginning of the array which will contain all the bytes received */
extern uint8_t * frame;

/* Initialization of the serial port as an interruption trigger*/
void serial_init(void);

#endif
