#include "clocks.h"
#include "led_irq_uart.h"
/* This file contains the main function of be booted and executed. It will be used to test:
  - Some Fibonacci's sequence elements usign a recursive function (call fibo(int)
  - The interaction with 3 LEDs of the board
  - The Interaction with the serial port
  - The Interation with a LED matrix. Call test_pixel() and test_image() */

int fibo(int i);

int main()
{
  clocks_init();
  irq_init();
  serial_init();
  while (1)
  {
    //read_print_pixels(frame);
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