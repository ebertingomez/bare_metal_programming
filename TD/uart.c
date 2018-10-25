#include "uart.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"
/* This file provides a set of functions to send values to and read information from
the serial port. */

/* Initialization of all the registers related to the serial port USART1 */
void uart_init(int baudrate)
{
    /* Clocks initialization ; PCLK=80MHz*/
    SET_BIT(RCC->APB2ENR, RCC_APB2ENR_USART1EN);
    CLEAR_BIT(RCC->CCIPR, RCC_CCIPR_USART1SEL);
    /* TX/RX pins initialization*/
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE6_Msk, GPIO_MODER_MODE6_1);
    MODIFY_REG(GPIOB->MODER, GPIO_MODER_MODE7_Msk, GPIO_MODER_MODE7_1);
    /* Selection of USART as the function for TX/RX*/
    GPIOB->AFR[0] = (GPIOB->AFR[0] | GPIO_AFRL_AFSEL6_Msk) & ~GPIO_AFRL_AFSEL6_3;
    GPIOB->AFR[0] = (GPIOB->AFR[0] | GPIO_AFRL_AFSEL7_Msk) & ~GPIO_AFRL_AFSEL7_3;
    /* Reset/Set of the serial port */
    SET_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
    CLEAR_BIT(RCC->APB2RSTR, RCC_APB2RSTR_USART1RST);
    /* Disable of USART1 for setting the parameters of the serial port*/
    CLEAR_BIT(USART1->CR1, USART_CR1_UE);
    /* Setting up the serial port speed */
    WRITE_REG(USART1->BRR, (uint16_t)(80000000 / baudrate));
    /* Setting up and activation of the serial port (8N1 with oversampling of 16) */
    WRITE_REG(USART1->CR1, 0);
    WRITE_REG(USART1->CR2, 0);
    USART1->CR1 |= USART_CR1_TE | USART_CR1_RE | USART_CR1_UE;
}
/* Print a 8bit word through the serial port*/
static void uart_putchar(uint8_t c)
{
    while (READ_BIT(USART1->ISR, USART_ISR_TXE) == 0)
    {
    }
    WRITE_REG(USART1->TDR, c);
}
/* Read a 8bit value from the serial port */
uint8_t uart_getchar()
{
    /* Check if a byte was received or if there was an error */
    while (!READ_BIT(USART1->ISR, USART_ISR_RXNE) ||
           READ_BIT(USART1->ISR, USART_ISR_FE) ||
           READ_BIT(USART1->ISR, USART_ISR_ORE))
    {
        /* If overrun error */
        if (READ_BIT(USART1->ISR, USART_ISR_ORE))
        {
            READ_REG(USART1->RDR);
            SET_BIT(USART1->ICR, USART_ICR_ORECF);
        }
        /* If framing error */
        else if (READ_BIT(USART1->ISR, USART_ISR_FE))
        {
            READ_REG(USART1->RDR);
            SET_BIT(USART1->ICR, USART_ICR_FECF);
        }
    }
    return READ_REG(USART1->RDR);
}
/* Print a sequence of characters through the serial port followed by a 
new line character '\n'. It is equivalent to puts*/
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
/* Read a sequence of 8bits words from the serial port. It stops when a new line character '\n'
is read or when size-1 values have been read. Equivalent to fgets */
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
/* Calculate the sum of a stream of 8bit numbers read from the serial port. */
uint32_t sum_of_hex()
{
    uint32_t volatile totalSum = 0;
    for (;;)
    {
        totalSum += uart_getchar();
    }

    return totalSum;
}