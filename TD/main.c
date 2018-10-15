#include "led.h"
#include "clocks.h"
#include "uart.h"
#include "matrix.h"
/* This file contains the main function of be booted and executed. It will be used to test:
  - Some Fibonacci's sequence elements usign a recursive function (call fibo(int)
  - the interaction with 3 LEDs of a board*/


int fibo(int i);

int main()
{
  test_pixels();
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