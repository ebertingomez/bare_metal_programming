#ifndef MATRIX_H
#define MATRIX_H
#include <stdint.h>
#include <stddef.h>

/* This file provides a set of function to initialize and control all the 
LEDs from a matrix. To test it, please call the function test_pixels() */

/* Test if the configuration is correct. It shows a sequence of red rows, then a red sequence
and a blue sequence of rows  */
void test_pixels(void);

/* Test if it is possible to read a raw binary file and represent its information using
the LED matrix  */
void test_image(void);

/* Read raw binary information and represent its information using the LED matrix  */
void read_print_pixels(uint8_t * pixels);
#endif