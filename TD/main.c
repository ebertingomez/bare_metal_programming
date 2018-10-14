#include "led.h"
#include "clocks.h"
#include "uart.h"
/* This file contains the main function of be booted and executed. It will be used to test:
  - Some Fibonacci's sequence elements usign a recursive function (call fibo(int)
  - the interaction with 3 LEDs of a board*/


int fibo(int i);

int main()
{
  clocks_init();
  led_init();
  uart_init();
  /*
  size_t sizemax = 1024;
  const char *string1 = "\rWrite something please: \r\n";
  const char *string2 = "\rYou wrote: \r";
  uint8_t s[sizemax];
  
  for(int i=0; i<10; i++)
  {
    uart_puts((uint8_t *)string1);
    uart_gets(s, sizemax);
    uart_puts((uint8_t *)string2);
    uart_puts(s);
  }
  */
  /* ./checksum.py -p /dev/cu.usbmodem000770868477 -v -n 100 */
  uint32_t sumPython = sum_of_hex(100);
  return sumPython;
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