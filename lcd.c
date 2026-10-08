#include <reg52.h>

/* Function from delay.c */
void delay_ms(unsigned int ms);


/* =================================================
   LCD CONNECTION

   RS  -> P3.0 -> AT89S52 Pin 10
   EN  -> P3.1 -> AT89S52 Pin 11
   RW  -> GND

   D0-D7 -> P2.0-P2.7
   ================================================= */

sbit LCD_RS = P3^0;
sbit LCD_EN = P3^1;

#define LCD_DATA P2


/* =================================================
   LCD ENABLE PULSE
   ================================================= */

void lcd_enable(void)
{
    LCD_EN = 1;
    delay_ms(1);

    LCD_EN = 0;
    delay_ms(1);
}


/* =================================================
   LCD COMMAND
   ================================================= */

void lcd_cmd(unsigned char cmd)
{
    LCD_RS = 0;

    LCD_DATA = cmd;

    lcd_enable();

    delay_ms(2);
}


/* =================================================
   LCD DATA
   ================================================= */

void lcd_data(unsigned char value)
{
    LCD_RS = 1;

    LCD_DATA = value;

    lcd_enable();

    delay_ms(2);
}


/* =================================================
   LCD INITIALIZATION
   ================================================= */

void lcd_init(void)
{
    delay_ms(20);

    lcd_cmd(0x38);     /* 8-bit, 2-line */
    lcd_cmd(0x0C);     /* Display ON, cursor OFF */
    lcd_cmd(0x01);     /* Clear display */
    lcd_cmd(0x06);     /* Entry mode */
    lcd_cmd(0x80);     /* First line */
}


/* =================================================
   LCD STRING
   ================================================= */

void lcd_string(char *str)
{
    while(*str)
    {
        lcd_data(*str);
        str++;
    }
}