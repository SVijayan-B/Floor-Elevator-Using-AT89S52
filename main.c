#include <reg52.h>


/* =================================================
   FUNCTION DECLARATIONS

   No .h files are used.
   ================================================= */


/* ----- Delay ----- */

void delay_ms(unsigned int ms);


/* ----- LCD ----- */

void lcd_init(void);
void lcd_cmd(unsigned char cmd);
void lcd_data(unsigned char value);
void lcd_string(char *str);


/* ----- Keypad ----- */

unsigned char keypad_getkey(void);


/* ----- Motor ----- */

void motor_up(void);
void motor_down(void);
void motor_stop(void);


/* ----- Floor ----- */

unsigned char get_current_floor(void);


/* ----- 7-Segment ----- */

void display_floor(unsigned char floor);
void display_off(void);


/* =================================================
   DISPLAY CURRENT FLOOR
   ================================================= */

void show_current_floor(unsigned char floor)
{
    lcd_cmd(0x01);

    if(floor <= 3)
    {
        lcd_string("CURRENT FLOOR:");

        lcd_cmd(0xC0);

        lcd_data('0' + floor);
    }
    else
    {
        lcd_string("FLOOR UNKNOWN");
    }
}


/* =================================================
   DISPLAY DESTINATION
   ================================================= */

void show_destination(unsigned char target)
{
    lcd_cmd(0x01);

    lcd_string("DESTINATION:");

    lcd_cmd(0xC0);

    lcd_string("FLOOR ");

    lcd_data('0' + target);
}


/* =================================================
   DISPLAY MOVING UP
   ================================================= */

void show_moving_up(unsigned char target)
{
    lcd_cmd(0x01);

    lcd_string("MOVING UP");

    lcd_cmd(0xC0);

    lcd_string("TO FLOOR ");

    lcd_data('0' + target);
}


/* =================================================
   DISPLAY MOVING DOWN
   ================================================= */

void show_moving_down(unsigned char target)
{
    lcd_cmd(0x01);

    lcd_string("MOVING DOWN");

    lcd_cmd(0xC0);

    lcd_string("TO FLOOR ");

    lcd_data('0' + target);
}


/* =================================================
   DISPLAY ARRIVAL
   ================================================= */

void show_arrived(unsigned char floor)
{
    lcd_cmd(0x01);

    lcd_string("REACHED FLOOR");

    lcd_cmd(0xC0);

    lcd_string("FLOOR ");

    lcd_data('0' + floor);
}


/* =================================================
   DISPLAY ALREADY THERE
   ================================================= */

void show_already_there(unsigned char floor)
{
    lcd_cmd(0x01);

    lcd_string("ALREADY AT");

    lcd_cmd(0xC0);

    lcd_string("FLOOR ");

    lcd_data('0' + floor);
}


/* =================================================
   MAIN PROGRAM
   ================================================= */

void main(void)
{
    unsigned char current_floor;
    unsigned char target_floor;
    unsigned char key;

    unsigned char moving;


    /* =================================================
       INITIALIZATION
       ================================================= */

    motor_stop();

    lcd_init();

    display_off();

    P1 = 0xFF;

    target_floor = 255;

    moving = 0;


    /* =================================================
       STARTUP MESSAGE
       ================================================= */

    lcd_cmd(0x01);

    lcd_string("ELEVATOR READY");

    delay_ms(1000);


    /* =================================================
       MAIN CONTROL LOOP
       ================================================= */

    while(1)
    {

        /* =============================================
           READ CURRENT FLOOR
           ============================================= */

        current_floor = get_current_floor();


        /* =============================================
           UPDATE 7-SEGMENT

           7-segment always shows current floor.
           ============================================= */

        if(current_floor <= 3)
        {
            display_floor(current_floor);
        }
        else
        {
            display_off();
        }


        /* =================================================
           ELEVATOR IS NOT MOVING
           ================================================= */

        if(moving == 0)
        {

            /* -----------------------------------------
               Read keypad
               ----------------------------------------- */

            key = keypad_getkey();


            /* =========================================
               VALID DESTINATION

               0 = Ground
               1 = Floor 1
               2 = Floor 2
               3 = Floor 3
               ========================================= */

            if(key == '0' ||
               key == '1' ||
               key == '2' ||
               key == '3')
            {

                target_floor = key - '0';


                /* -------------------------------------
                   Show destination
                   ------------------------------------- */

                show_destination(target_floor);

                delay_ms(500);


                /* =====================================
                   CASE 1:
                   ALREADY AT DESTINATION
                   ===================================== */

                if(current_floor == target_floor)
                {

                    motor_stop();

                    show_already_there(target_floor);

                    delay_ms(1000);

                    target_floor = 255;
                }


                /* =====================================
                   CASE 2:
                   MOVE UP
                   ===================================== */

                else if(current_floor < target_floor)
                {

                    motor_up();

                    moving = 1;

                    show_moving_up(target_floor);
                }


                /* =====================================
                   CASE 3:
                   MOVE DOWN
                   ===================================== */

                else if(current_floor > target_floor)
                {

                    motor_down();

                    moving = 1;

                    show_moving_down(target_floor);
                }
            }


            /* =========================================
               INVALID KEYS

               4-9, *, #
               ========================================= */

            else if(key != 0)
            {

                lcd_cmd(0x01);

                lcd_string("INVALID FLOOR");

                delay_ms(700);
            }


            /* =========================================
               NO KEY PRESSED
               ========================================= */

            else
            {

                if(current_floor <= 3)
                {
                    show_current_floor(current_floor);
                }
            }
        }


        /* =================================================
           ELEVATOR IS MOVING
           ================================================= */

        else
        {

            /* -----------------------------------------
               Valid floor sensor detected?
               ----------------------------------------- */

            if(current_floor <= 3)
            {

                /* =====================================
                   TARGET REACHED
                   ===================================== */

                if(current_floor == target_floor)
                {

                    motor_stop();

                    moving = 0;

                    show_arrived(target_floor);

                    delay_ms(1500);

                    target_floor = 255;
                }


                /* =====================================
                   TARGET NOT REACHED

                   Continue in correct direction.
                   ===================================== */

                else
                {

                    if(current_floor < target_floor)
                    {
                        motor_up();
                    }
                    else
                    {
                        motor_down();
                    }
                }
            }
        }


        /* ---------------------------------------------
           Small control delay
           --------------------------------------------- */

        delay_ms(100);
    }
}