#include "led.h"
#include <stdint.h>

#define GPIO_CLOCK_REG (*(volatile uint32_t *)0x4002104c)
#define GPIOB5_MODE_REG (*(volatile uint32_t *)0x48000400)
#define GPIOB5_VALUE_REG (*(volatile uint32_t *)0x48000418)

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
}

void led_g_on()
{
    GPIOB5_VALUE_REG = (GPIOB5_VALUE_REG & ~(1<<30)) | (1<<14);
}
void led_g_off()
{
    GPIOB5_VALUE_REG = (GPIOB5_VALUE_REG & ~(1<<14)) | (1<<30);
}
//TODO: void led(int a){}