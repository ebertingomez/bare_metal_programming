#include "led.h"
#include "clocks.h"
#include "uart.h"

int fibo(int i);

int main()
{
  clocks_init();
  uart_putchar(0x44);
  uart_putchar(0x45);
  uart_putchar(0x46);
  uart_putchar(0x47);

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