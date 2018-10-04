#include <stdio.h>
#include <stdlib.h>

const int a = 1;
int c = 4;
int d = 0;

void funct();

int main()
{
  int e = 10;
  int f = 12;
  int *g = (int *)malloc(32);
  // Pointers
  const int *a1 = &a;
  int *c1 = &c;
  int *d1 = &d;
  int *e1 = &e;
  int *f1 = &f;

  printf("Address: funct() = %p\n", funct);
  printf("Address: const int a = %p \n", a1);
  printf("Address: int c = %p \n", c1);
  printf("Address: int d = %p \n", d1);
  printf("Address: int e = %p \n", e1);
  printf("Address: int f = %p \n", f1);
  printf("Address: int * g = %p \n", g);
  return 0;
}

void funct()
{
  int e = 1024;
  e = e + 24;
}
