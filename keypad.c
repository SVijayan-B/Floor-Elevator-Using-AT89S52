#include <reg52.h>

/* Function from delay.c */
void delay_ms(unsigned int ms);


/* =================================================
   KEYPAD CONNECTION

   COLUMNS:

   P1.0 -> keypad 1
   P1.1 -> keypad 2
   P1.2 -> keypad 3

   ROWS:

   P1.3 -> keypad A
   P1.4 -> keypad B
   P1.5 -> keypad C
   P1.6 -> keypad D

   P1.7 -> unused


   KEYPAD LAYOUT:

       1   2   3
       4   5   6
       7   8   9
       *   0   #

   ================================================= */

#define KEYPAD P1


/* =================================================
   KEYPAD SCANNER
   ================================================= */

unsigned char keypad_getkey(void)
{
    unsigned char value;


    /* =============================================
       ROW A
       Keys: 1 2 3

       P1.3 = 0
       ============================================= */

    KEYPAD = 0xF7;

    value = KEYPAD & 0x07;

    if(value != 0x07)
    {
        delay_ms(20);

        value = KEYPAD & 0x07;

        if(value == 0x06)
        {
            while((KEYPAD & 0x07) != 0x07);
            return '1';
        }

        if(value == 0x05)
        {
            while((KEYPAD & 0x07) != 0x07);
            return '2';
        }

        if(value == 0x03)
        {
            while((KEYPAD & 0x07) != 0x07);
            return '3';
        }
    }


    /* =============================================
       ROW B
       Keys: 4 5 6

       P1.4 = 0
       ============================================= */

    KEYPAD = 0xEF;

    value = KEYPAD & 0x07;

    if(value != 0x07)
    {
        delay_ms(20);

        value = KEYPAD & 0x07;

        if(value == 0x06)
        {
            while((KEYPAD & 0x07) != 0x07);
            return '4';
        }

        if(value == 0x05)
        {
            while((KEYPAD & 0x07) != 0x07);
            return '5';
        }

        if(value == 0x03)
        {
            while((KEYPAD & 0x07) != 0x07);
            return '6';
        }
    }


    /* =============================================
       ROW C
       Keys: 7 8 9

       P1.5 = 0
       ============================================= */

    KEYPAD = 0xDF;

    value = KEYPAD & 0x07;

    if(value != 0x07)
    {
        delay_ms(20);

        value = KEYPAD & 0x07;

        if(value == 0x06)
        {
            while((KEYPAD & 0x07) != 0x07);
            return '7';
        }

        if(value == 0x05)
        {
            while((KEYPAD & 0x07) != 0x07);
            return '8';
        }

        if(value == 0x03)
        {
            while((KEYPAD & 0x07) != 0x07);
            return '9';
        }
    }


    /* =============================================
       ROW D
       Keys: * 0 #

       P1.6 = 0
       ============================================= */

    KEYPAD = 0xBF;

    value = KEYPAD & 0x07;

    if(value != 0x07)
    {
        delay_ms(20);

        value = KEYPAD & 0x07;

        if(value == 0x06)
        {
            while((KEYPAD & 0x07) != 0x07);
            return '*';
        }

        if(value == 0x05)
        {
            while((KEYPAD & 0x07) != 0x07);
            return '0';
        }

        if(value == 0x03)
        {
            while((KEYPAD & 0x07) != 0x07);
            return '#';
        }
    }


    /* No key pressed */

    return 0;
}