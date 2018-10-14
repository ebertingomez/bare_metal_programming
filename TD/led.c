#include "led.h"
#include "stm32l475xx.h"
#include "stm32l4xx.h"

/* This file provides a set of functions to control three LEDs from
our board, a red, a blue and a green one. */

/* Initialization of the clocks of each GPIO and their mode as output */
void led_init()
{
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOBEN);
    SET_BIT(RCC->AHB2ENR, RCC_AHB2ENR_GPIOCEN);
    
    MODIFY_REG(GPIOB->MODER,GPIO_MODER_MODE14_Msk,GPIO_MODER_MODE14_0);
    MODIFY_REG(GPIOC->MODER,GPIO_MODER_MODE9_Msk,GPIO_MODER_MODE9_0);
}

/* Turn on the green LED */
void led_g_on()
{
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BS_14);
}

/* Turn off the green LED */
void led_g_off()
{
    SET_BIT(GPIOB->BSRR, GPIO_BSRR_BR_14);
}

/* Turn on/off the yellow and blue LEDs */
void led(state s)
{
    led_init();
    switch (s)
    {
    case LED_OFF:
        CLEAR_BIT(GPIOC->MODER, GPIO_MODER_MODE9_Msk);
        break;
    case LED_YELLOW:
        SET_BIT(GPIOC->BSRR, GPIO_BSRR_BS_9);
        break;
    case LED_BLUE:
        SET_BIT(GPIOC->BSRR, GPIO_BSRR_BR_9);
        break;
    default:
        break;
    }
}