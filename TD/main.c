#include "led.h"

int fibo(int i);

int main()
{
  led_init();
  led_g_off();
  while (1)
  {
    led_g_on();
    for (int i = 0; i < 1000000; i++)
    {
      asm volatile("nop");
    }
    led_g_off();
    led(LED_YELLOW);
    for (int i = 0; i < 1000000; i++)
    {
      asm volatile("nop");
    }
    led(LED_BLUE);
    for (int i = 0; i < 1000000; i++)
    {
      asm volatile("nop");
    }
    led(LED_OFF);
  }

  return 0;
}

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