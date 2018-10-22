#include "buttons.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"
#include "led.h"
#include <stdint.h>

void button_init()
{
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);
    CLEAR_BIT(GPIOC->MODER, GPIO_MODER_MODE13_Msk);
    SET_BIT(EXTI->IMR1, EXTI_IMR1_IM13);
    SET_BIT(EXTI->FTSR1, EXTI_FTSR1_FT13);
    MODIFY_REG(SYSCFG->EXTICR[3], SYSCFG_EXTICR4_EXTI13_Msk, SYSCFG_EXTICR4_EXTI13_PC);
    NVIC_EnableIRQ(40);
    led_init();
    led(LED_OFF);
}

void EXTI15_10_IRQHandler()
{
    SET_BIT(EXTI->PR1, EXTI_PR1_PIF13);
    led_g_on();
    for (int i = 0; i < 200000; i++)
    {
        asm volatile("nop");
    }
    led_g_off();
}