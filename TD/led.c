#include "led.h"
#include <stdint.h>

#define GPIO_CLOCK_REG (*(volatile uint32_t *)0x4002104c)
#define GPIOB5_MODE_REG (*(volatile uint32_t *)0x48000400)
#define GPIOB5_VALUE_REG (*(volatile uint32_t *)0x48000418)

#define PC9_MODE_REG (*(volatile uint32_t *)0x48000800)
#define PC9_VALUE_REG (*(volatile uint32_t *)0x48000818)

enum state
{
    LED_OFF = 0,
    LED_YELLOW = 1,
    LED_BLUE = 2
};

void led_init()
{
    GPIO_CLOCK_REG |= (1 << 1);
    GPIOB5_MODE_REG = (GPIOB5_MODE_REG | (1 << 28)) & ~(1 << 29);

    PC9_MODE_REG = (PC9_MODE_REG | (1 << 18)) & ~(1 << 19);
}

void led_g_on()
{
    GPIOB5_VALUE_REG |= (1 << 14);
}
void led_g_off()
{
    GPIOB5_VALUE_REG |= (1 << 30);
}
void led(int s)
{

    switch (s)
    {
    case LED_OFF:
        PC9_VALUE_REG = PC9_VALUE_REG;
        break;
    case LED_YELLOW:
        PC9_VALUE_REG |= (1 << 9);
        break;

    case LED_BLUE:
        PC9_VALUE_REG |= (1 << 25);
        break;

    default:
        break;
    }
}