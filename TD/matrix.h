#ifndef MATRIX_H
#define MATRIX_H
#include <stdint.h>
#include <stddef.h>

/* Test if the configuration is correct. It shows a sequence of red rows, then a red sequence
and a blue sequence of rows  */
void test_pixels(void);

/* Test if it is possible to read a raw binary file and represent its information using
the LED matrix  */
void test_image(void);
#endif