#ifndef LED_IRQ_UART_H

#define LED_IRQ_UART_H
#include "uart.h"
#include "matrix.h"
#include "irq.h"

extern uint8_t * frame;

void serial_init(void);

#endif
