#include "led_irq_uart.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"

static uint8_t array[192];
static int counter=0;
static uint8_t byte;
uint8_t * frame = array;

void EXTI9_5_IRQHandler(void);

void serial_init()
{
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM7);
    SET_BIT(EXTI->FTSR1, EXTI_FTSR1_FT7);
    MODIFY_REG(SYSCFG->EXTICR[1], SYSCFG_EXTICR2_EXTI7_Msk, SYSCFG_EXTICR2_EXTI7_PB);
    NVIC_EnableIRQ(23);
}

void EXTI9_5_IRQHandler()
{
    byte = uart_getchar();
    SET_BIT(EXTI->PR1, EXTI_PR1_PIF7);
    if (byte == (uint8_t)0xFF || counter==192)
    {
        counter=0;
    }
    else
    {
        array[counter] = byte;
        counter++;
    }
}