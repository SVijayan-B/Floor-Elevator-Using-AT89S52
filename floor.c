#include <reg52.h>


/* =================================================
   FLOOR SENSOR CONNECTIONS

   SW0 -> P3.4 -> Pin 14 -> FLOOR 0
   SW1 -> P3.5 -> Pin 15 -> FLOOR 1
   SW2 -> P3.6 -> Pin 16 -> FLOOR 2
   SW3 -> P3.7 -> Pin 17 -> FLOOR 3

   ACTIVE LOW:

   0 = sensor active
   1 = sensor inactive

   ================================================= */

sbit FLOOR0 = P3^4;
sbit FLOOR1 = P3^5;
sbit FLOOR2 = P3^6;
sbit FLOOR3 = P3^7;


/* =================================================
   GET CURRENT FLOOR
   ================================================= */

unsigned char get_current_floor(void)
{
    if(FLOOR0 == 0)
    {
        return 0;
    }

    if(FLOOR1 == 0)
    {
        return 1;
    }

    if(FLOOR2 == 0)
    {
        return 2;
    }

    if(FLOOR3 == 0)
    {
        return 3;
    }

    return 255;
}