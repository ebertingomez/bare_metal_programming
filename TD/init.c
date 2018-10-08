#include <stdint.h>

extern uint32_t start_of_BSS;
extern uint32_t size_of_BSS;
void init_bss()
{
    uint32_t i = 0;
    uint8_t *p;
    p = (uint8_t *)&start_of_BSS;
    uint32_t size = (uint32_t)&size_of_BSS;
    while (i < size)
    {
        *p = 0;
        p++;
        i++;
    }
}