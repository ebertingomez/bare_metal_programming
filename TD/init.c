#include <stdint.h>
/*This file provides a function to empty the bss section of a board before a executable
is booted*/
extern uint8_t _bstart, _bend, _dstartROM, _dstartRAM, _dendRAM, _tstartROM, _tstartRAM, _tendRAM, _astartROM, _astartRAM, _aendRAM;

/* Set all the values from the bss to zero */
void init_bss()
{
    for (uint8_t *p = &_bstart; p < &_bend; p++)
        *p = 0;
}

/* Copy all the values from data ROM to data RAM */
void init_data()
{
    uint8_t * r = &_dstartROM;
    for (uint8_t *p = &_dstartRAM; p < &_dendRAM; p++)
    {
        *p = *r;
        r++;
    }
}

/* Copy all the values from .arm ROM to .arm RAM. This section contains the vector table */
void init_arm()
{
    uint8_t * r = &_astartROM;
    for (uint8_t *p = &_astartRAM; p < &_aendRAM; p++)
    {
        *p = *r;
        r++;
    }
}

/* Copy all the values from text ROM to text RAM */
void init_text()
{
    uint8_t * r = &_tstartROM;
    for (uint8_t *p = &_tstartRAM; p < &_tendRAM; p++)
    {
        *p = *r;
        r++;
    }
}
