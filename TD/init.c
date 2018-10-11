#include <stdint.h>
/*This file provides a function to empty the bss section of a board before a executable
is booted*/
extern uint8_t _bstart, _bend;
void init_bss()
{
    for (uint8_t *p = &_bstart; p < &_bend; p++)
        *p = 0;
}