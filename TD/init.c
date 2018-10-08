#include <stdint.h>
extern uint8_t _bstart, _bend;
void init_bss()
{
    for(uint8_t *p=&_bstart; p<&_bend;p++)
        *p = 0;
}