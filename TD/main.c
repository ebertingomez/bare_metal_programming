#include "clocks.h"
#include "matrix.h"
#include "irq.h"
#include "buttons.h"
/* This file contains the main function to be booted and executed. It will be used to test:
  - Some Fibonacci's sequence elements usign a recursive function (call fibo(int)
  - The interaction with 3 LEDs of the board
  - The Interaction with the serial port
  - The Interation with a LED matrix. Call test_pixel() and test_image()
  - Interruptions generated by the USER button
  */

int fibo(int i);

int main()
{
  clocks_init();
  irq_init();
  button_init();
  while (1)
  {
    test_image();
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