#include <reg52.h>


/* =================================================
   7-SEGMENT DISPLAY

   P0.0 -> a
   P0.1 -> b
   P0.2 -> c
   P0.3 -> d
   P0.4 -> e
   P0.5 -> f
   P0.6 -> g
   P0.7 -> dp

   Common cathode assumed.

   ================================================= */

#define SEGMENT P0


/* =================================================
   DISPLAY FLOOR
   ================================================= */

void display_floor(unsigned char floor)
{
    switch(floor)
    {
        case 0:
            SEGMENT = 0x3F;
            break;

        case 1:
            SEGMENT = 0x06;
            break;

        case 2:
            SEGMENT = 0x5B;
            break;

        case 3:
            SEGMENT = 0x4F;
            break;

        default:
            SEGMENT = 0x00;
            break;
    }
}


/* =================================================
   DISPLAY OFF
   ================================================= */

void display_off(void)
{
    SEGMENT = 0x00;
}