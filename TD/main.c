#include "led.h"
#include "clocks.h"
#include "uart.h"
/* This file contains the main function of be booted and executed. It will be used to test:
  - Some Fibonacci's sequence elements usign a recursive function (call fibo(int)
  - The interaction with 3 LEDs of the board
  - The Interaction with the serial port*/

int fibo(int i);

int main()
{
  /*Initialization of all the modules */
  clocks_init();
  led_init();
  uart_init();
  
  /* Initialization of the variables*/
  const size_t sizemax = 1024;
  const char *string1 = "\rWrite something please: \r\n";
  const char *string2 = "\rYou wrote: \r";
  uint8_t s[sizemax];
  
  for(int i=0; i<2; i++)
  {
    uart_puts((uint8_t *)string1);
    uart_gets(s, sizemax);
    uart_puts((uint8_t *)string2);
    uart_puts(s);
  }
  uint32_t sumPython = sum_of_hex();
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