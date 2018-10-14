#include "uart.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"

void uart_init()
{

    /* Clocks initialization ; PCLK=80MHz*/
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
    CLEAR_BIT(RCC->CCIPR, RCC_CCIPR_USART1SEL);

    /* Pins initialization */
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE6_Msk, GPIO_MODER_MODE6_1);
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE7_Msk, GPIO_MODER_MODE7_1);
    GPIOB->AFR[0] = (GPIOB->AFR[0] | GPIO_AFRL_AFSEL6_Msk) & ~GPIO_AFRL_AFSEL6_3;
    GPIOB->AFR[0] = (GPIOB->AFR[0] | GPIO_AFRL_AFSEL7_Msk) & ~GPIO_AFRL_AFSEL7_3;

    /* Serial port initialization */
    SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
    CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
    CLEAR_BIT(USART1->CR1, USART_CR1_UE);
    WRITE_REG(USART1->BRR, 694);
    WRITE_REG(USART1->CR1, 0);
    WRITE_REG(USART1->CR2, 0);
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}

void uart_putchar(uint8_t c)
{

    while (READ_BIT(USART1->ISR, USART_ISR_TXE) == 0)
    {
    }
    WRITE_REG(USART1->TDR, c);
}
uint8_t uart_getchar()
{
    while (READ_BIT(USART1->ISR, USART_ISR_RXNE) == 0)
    {
    }
    return READ_REG(USART1->RDR);
}
void uart_puts(const uint8_t *s)
{
    int i = 0;
    while (*(s + i) != '\0')
    {
        uart_putchar(*(s + i));
        i++;
    }
    uart_putchar('\n');
}

void uart_gets(uint8_t *s, size_t size)
{
    size_t i = 0;
    do
    {
        *(s + i) = uart_getchar();
        i++;
    } while (*(s + i - 1) != '\n' && i < size - 1);
    *(s + i) = '\0';
}

uint32_t sum_of_hex(int size)
{
    uint32_t totalSum = 0;
    uint8_t array[size];
    for (int i = 0; i < size; i++)
    {
        array[i] = uart_getchar();
    }

    for (int i = 0; i < size; i++)
    {
        totalSum = totalSum + array[i];
    }

    return totalSum;
}