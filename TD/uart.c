#include "uart.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"

void uart_init()
{
    /* Pins initialization */
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE6_Msk) | GPIO_MODER_MODE6_1;
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE7_Msk) | GPIO_MODER_MODE7_1;
    GPIOB->AFR[0] = (GPIOB->AFR[0] & GPIO_AFRL_AFRL6) & ~GPIO_AFRL_AFSEL6_3;
    GPIOB->AFR[0] = (GPIOB->AFR[0] & GPIO_AFRL_AFRL7) & ~GPIO_AFRL_AFSEL7_3;

    /* Clocks initialization ; PCLK=80MHz*/
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
    CLEAR_BIT(RCC->CCIPR, RCC_CCIPR_USART1SEL);

    /* Serial port initialization */
    SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
    WRITE_REG(USART1->BRR, 694);
    WRITE_REG(USART1->CR1, 0);
    WRITE_REG(USART1->CR2, 0);
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE;
}

void uart_putchar(uint8_t c)
{

    while (READ_BIT(USART1->ISR, USART_ISR_TXE) != 0)
    {
    }
            WRITE_REG(USART1->TDR, c);

}
uint8_t uart_getchar()
{ 
    while (READ_BIT(USART1->ISR, USART_ISR_RXNE) != 0)
    {
        
    }
    return READ_REG(USART1->RDR);

}
void uart_puts(const uint8_t *s)
{ //TODO
}
void uart_gets(uint8_t *s, size_t size)
{ //TODO
}