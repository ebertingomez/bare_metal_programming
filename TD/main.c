#include "led.h"
#include "clocks.h"
#include "uart.h"

int fibo(int i);

int main()
{
  clocks_init();
  led_init();
  uart_init();
  while (1)
  {
    led_g_on();
    led_g_off();
    uart_putchar('a');
    led_g_on();
    led_g_off();
    uart_putchar('b');
    led_g_on();
    led_g_off();
    uart_putchar('c');
    led_g_on();
    led_g_off();
    uart_putchar('d');
    led_g_on();
    led_g_off();
    uint8_t b = uart_getchar();
    led_g_on();
    led_g_off();
    uart_putchar(b);
    led_g_on();
    led_g_off();
    uint8_t c = uart_getchar();
    led_g_on();
    led_g_off();
    uart_putchar(c);
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