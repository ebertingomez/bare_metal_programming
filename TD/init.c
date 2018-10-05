#include <stdint.h>
void init_bss()
{
    extern uint32_t start_of_BSS, size_of_BSS;
    for (uint32_t i = 0; i < size_of_BSS; i = i + 32)
    {
        uint32_t *p;
        p = (uint32_t * )start_of_BSS + i;
        *p = 0;
    }
}