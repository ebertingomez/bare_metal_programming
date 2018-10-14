#ifndef LED_H
#define LED_H

typedef enum
{
    LED_OFF = 0,
    LED_YELLOW = 1,
    LED_BLUE = 2
} state;

void led_init(void);
void led_g_on(void);
void led_g_off(void);
void led(state);

#endif