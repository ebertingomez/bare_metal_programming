#include "led.h"
#include <stdint.h>


#define GPIO_CLOCK_REG (*(volatile uint32_t *)0x4800044c)
#define GPIOB5_REG (*(volatile uint32_t *)0x48000400)

enum state
{
    LED_OFF = 0,
    LED_YELLOW = 1,
    LED_BLUE = 2
};

void led_init()
{
    GPIO_CLOCK_REG = 0x00000002;
    GPIOB5_REG = 0xDFFFFEBF;

}

void led_g_on()
{
    //TODO
}
void led_g_off()
{
    //TODO
}
void led(state)
{
    //TODO
}