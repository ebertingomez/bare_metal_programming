#include "led.h"
#include "clocks.h"
#include "uart.h"

int fibo(int i);

int main()
{
  clocks_init();
  uart_init();
  while (1)
  {
    uart_putchar('a');
    uart_putchar('b');
    uart_putchar('c');
    uart_putchar('d');
    uint8_t b = uart_getchar();

    uart_putchar(b);

    uint8_t c = uart_getchar();

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