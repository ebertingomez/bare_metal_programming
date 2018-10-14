#include "led.h"
#include "clocks.h"
#include "uart.h"

int fibo(int i);

int main()
{
  clocks_init();
  led_init();
  uart_init();
  size_t size = 1024;
  const char *string1 = "\rWrite something please: \r\n";
  const char *string2 = "\rYou wrote: \r";
  uint8_t s[size];
  while (1)
  {
    uart_puts((uint8_t *)string1);
    uart_gets(s, size);
    uart_puts((uint8_t *)string2);
    uart_puts(s);
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