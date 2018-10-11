#include "led.h"
#include "clocks.h"
/* This file contains the main function of be booted and executed. It will be used to test:
  - Some Fibonacci's sequence elements usign a recursive function (call fibo(int)
  - the interaction with 3 LEDs of a board*/
int fibo(int i);

int main()
{
  clocks_init();
  const int clk_freq = 20000000;
  led_init();
  led_g_off();
  led(LED_OFF);
  while (1)
  {
    led_g_on();
    for (int i = 0; i < clk_freq; i++)
    {
      asm volatile("nop");
    }
    led_g_off();
    led(LED_YELLOW);
    for (int i = 0; i < clk_freq; i++)
    {
      asm volatile("nop");
    }
    led(LED_BLUE);
    for (int i = 0; i < clk_freq; i++)
    {
      asm volatile("nop");
    }
    led(LED_OFF);
  }

  return 0;
}
/* This function let to calculate a fibonacci number based on recursivity*/
int fibo(int i)
{
  if (i == 1 || i == 2)
  {
    return 1;
  }
  else
  {
    return fibo(i - 2) + fibo(i - 1);
  }
}