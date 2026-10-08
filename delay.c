#include <reg52.h>

/* =================================================
   DELAY FUNCTION
   ================================================= */

void delay_ms(unsigned int ms)
{
    unsigned int i;
    unsigned int j;

    for(i = 0; i < ms; i++)
    {
        for(j = 0; j < 1275; j++)
        {
        }
    }
}