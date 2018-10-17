#ifndef LED_H
#define LED_H

/* This file provides a set of functions to control three LEDs from
our board, a red, a blue and a green one. */

/* This variable represents the state of the board in order to turn on
a specific LED */
typedef enum
{
    LED_OFF = 0,
    LED_YELLOW = 1,
    LED_BLUE = 2
} state;

/* Initialization of the clocks of each GPIO and their mode as output */
void led_init(void);
/* Turn on the green LED */
void led_g_on(void);
/* Turn off the green LED */
void led_g_off(void);
/* Turn on/off the yellow and blue LEDs */
void led(state);

#endif