#include "led.h"
#include <stdint.h>
#include "stm32l475xx.h"

/* This file provides a set of functions to control three LEDs from
our board, a red, a blue and a green one. */

/* Initialization of the clocks of each GPIO and their mode as output */
void led_init()
{
    RCC->AHB2ENR |= (RCC_AHB2ENR_GPIOBEN | RCC_AHB2ENR_GPIOCEN);
    GPIOB->MODER = (GPIOB->MODER & ~GPIO_MODER_MODE14_Msk) | GPIO_MODER_MODE14_0;

    GPIOC->MODER = (GPIOC->MODER & ~GPIO_MODER_MODE9_Msk) | GPIO_MODER_MODE9_0;
}

/* Turn on the green LED */
void led_g_on()
{
    GPIOB->BSRR |= GPIO_BSRR_BS_14;
}

/* Turn off the green LED */
void led_g_off()
{
    GPIOB->BSRR |= GPIO_BSRR_BR_14;
}

/* Turn on/off the yellow and blue LEDs */
void led(state s)
{
    led_init();
    switch (s)
    {
    case LED_OFF:
        GPIOC->MODER &= ~GPIO_MODER_MODE9_Msk;
        break;
    case LED_YELLOW:
        GPIOC->BSRR |= GPIO_BSRR_BS_9;
        break;
    case LED_BLUE:
        GPIOC->BSRR |= GPIO_BSRR_BR_9;
        break;
    default:
        break;
    }
}