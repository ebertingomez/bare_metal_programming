#include "led_irq_uart.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"

uint8_t array[192];
uint8_t * frame = array;

void serial_init()
{
    uart_init(38400);
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM26);
    SET_BIT(EXTI->FTSR1, EXTI_FTSR1_FT13);
    NVIC_EnableIRQ(44);
}

void USART1_IRQHandler()
{
    uint8_t byte = uart_getchar();
    if (byte == 0xFF)
    {
        frame = array;
    }
    else
    {
        *frame = byte;
        frame++;
    }
}