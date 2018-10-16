#ifndef UART_H
#define UART_H
#include <stdint.h>
#include <stddef.h>

void uart_init(void);
void uart_puts(const uint8_t *s);
void uart_gets(uint8_t *s, size_t size);
uint32_t sum_of_hex();

#endif