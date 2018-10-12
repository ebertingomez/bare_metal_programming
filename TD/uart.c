#include "uart.h"
#include "stm32l475xx.h"

void uart_init()
{
    /* Pins initialization */
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE4_Msk) | GPIO_MODER_MODE6_1;
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE5_Msk) | GPIO_MODER_MODE7_1;
    GPIOB->AFR[0] = (GPIOB->AFR[0] & GPIO_AFRL_AFRL6) & ~GPIO_AFRL_AFSEL6_3;
    GPIOB->AFR[0] = (GPIOB->AFR[0] & GPIO_AFRL_AFRL7) & ~GPIO_AFRL_AFSEL7_3;

    /* Clocks initialization ; PCLK=80MHz*/
    RCC->APB2ENR |= RCC_APB2ENR_USART1EN;
    RCC->CCIPR &= ~RCC_CCIPR_USART1SEL;

    /* Serial port initialization */
    RCC->APB2RSTR |= RCC_APB2RSTR_USART1RST;
    USART1->BRR 
}
void uart_putchar(uint8_t c)
{ //TODO
}
uint8_t uart_getchar()
{ //TODO
}
void uart_puts(const uint8_t *s)
{ //TODO
}
void uart_gets(uint8_t *s, size_t size)
{ //TODO
}