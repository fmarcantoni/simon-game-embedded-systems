/************** ECE2049 DEMO CODE ******************/
/**************  13 March 2019   ******************/
/***************************************************/

#include <msp430.h>
#include <stdlib.h>

/* Peripherals.c and .h are where the functions that implement
 * the LEDs and keypad, etc are. It is often useful to organize
 * your code by putting like functions together in files.
 * You include the header associated with that file(s)
 * into the main file of your project. */
#include "peripherals.h"
#include <string.h>
// Function Prototypes
void swDelay(char numLoops);
int pressed();
void setup();

// Declare globals here

// Main
void main(void)
{
    unsigned char currKey=0;

    WDTCTL = WDTPW | WDTHOLD;    // Stop watchdog timer. Always need to stop this!!
                                 // You can then configure it properly, if desired

    // Useful code starts here
    initLeds();

    configDisplay();
    configKeypad();

/**
 * main.c
 */
    int x = 1;
    unsigned char num [32];
    unsigned char input [32];
    int t = 3;
    int i = 0;
    int state = 0;
    int flag;
    int reset = 0;


    while(1){

        switch(state){

        case 0:
            x = 1;
            t = 3;
            Graphics_drawStringCentered(&g_sContext, "SIMON", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
            Graphics_flushBuffer(&g_sContext);
            currKey = getKey();
            if (currKey == '*'){
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
                swDelay(1);
                Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
                swDelay(1);
                Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
                swDelay(1);
                Graphics_clearDisplay(&g_sContext);
                Graphics_flushBuffer(&g_sContext);
                state = 1;

            }
            break;


        case 1:

            //Display LED Sequence
            for(i = 0; i < x; i++){
                num [x-1] = rand() % 4 + 1 ;

            }

            for(i = 0; i < x; i++){

                if(num[i] == 1){
                    setLeds(8);
                    Buzzer2(640);
                    swDelay(1);
                    BuzzerOff();
                    setLeds(0);

                }
                else if(num[i] == 2){
                    setLeds(4);
                     Buzzer2(740);
                     swDelay(1);
                     BuzzerOff();
                     setLeds(0);
                }
                else if(num[i] == 3){
                    setLeds(2);
                    Buzzer2(840);
                    swDelay(1);
                    BuzzerOff();
                    setLeds(0);
                }
                else if(num[i] == 4){
                    setLeds(1);
                    Buzzer2(940);
                    swDelay(1);
                    BuzzerOff();
                    setLeds(0);
                }
                swDelay(t);

            }
            state = 2;
            break;

        case 2:
            reset = 0;
            for (i = 0; i < x; i++){
                currKey = 0;
                while(currKey==0)
                {
                    currKey = getKey();
                    reset = pressed();
                    if(reset > 0){
                         state = 0;
                         break;
                   }
                }
                if(reset > 0){
                    state = 0;
                    break;
                }

                if (currKey == 49){
                    input[i] = currKey;
                    Graphics_drawStringCentered(&g_sContext, "1", AUTO_STRING_LENGTH, 15, 25, TRANSPARENT_TEXT);
                    Graphics_flushBuffer(&g_sContext);

                }
                else if (currKey == 50){
                    input[i] = currKey;
                    Graphics_drawStringCentered(&g_sContext, "2", AUTO_STRING_LENGTH, 35, 25, TRANSPARENT_TEXT);
                    Graphics_flushBuffer(&g_sContext);

                }
                else if (currKey == 51){
                    input[i] = currKey;
                    Graphics_drawStringCentered(&g_sContext, "3", AUTO_STRING_LENGTH, 55, 25, TRANSPARENT_TEXT);
                    Graphics_flushBuffer(&g_sContext);

                }
                else if (currKey == 52){
                    input[i] = currKey ;
                    Graphics_drawStringCentered(&g_sContext, "4", AUTO_STRING_LENGTH, 75, 25, TRANSPARENT_TEXT);
                    Graphics_flushBuffer(&g_sContext);
                }

                else{
                    Graphics_clearDisplay(&g_sContext);
                    Graphics_drawStringCentered(&g_sContext,"ERROR", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
                    //Graphics_drawStringCentered(&g_sContext, input, AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
                    Graphics_flushBuffer(&g_sContext);
                    state = 2;
                }
                swDelay(1);
                Graphics_flushBuffer(&g_sContext);
                Graphics_clearDisplay(&g_sContext);
            }

            if(reset > 0){
                state = 0;
                break;
            }

            state = 3;
            break;

        case 3:
            flag = 0;
            for (i = 0; i < x; i++){
                int y = 0;

                y = ((input[i]-0x30)== num[i]);
                if (y == 0){
                    Graphics_clearDisplay(&g_sContext);
                    Graphics_drawStringCentered(&g_sContext, "ERROR, WRONG KEY", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
                    Graphics_flushBuffer(&g_sContext);
                    swDelay(1);
                    Graphics_clearDisplay(&g_sContext);
                    Graphics_flushBuffer(&g_sContext);
                    state = 0;
                    flag = 1;
                }
            }
                if(flag!=1){
                    Graphics_clearDisplay(&g_sContext);
                    Graphics_drawStringCentered(&g_sContext, "CORRECT", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
                    Graphics_flushBuffer(&g_sContext);
                    swDelay(1);
                    Graphics_clearDisplay(&g_sContext);
                    Graphics_flushBuffer(&g_sContext);
                    state = 1;


                }

            x++;
            t = t - 0.025;

            if(x > 32){
                Graphics_clearDisplay(&g_sContext);
                Graphics_drawStringCentered(&g_sContext, "CONGRATULATIONS!", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
                Graphics_drawStringCentered(&g_sContext, "You won!", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);
                Graphics_flushBuffer(&g_sContext);
                swDelay(1);
                Graphics_clearDisplay(&g_sContext);
                state = 0;

            }
            break;
    }
    }
}




/*
    // *** Intro Screen ***
    Graphics_clearDisplay(&g_sContext); // Clear the display

    // Write some text to the display
    Graphics_drawStringCentered(&g_sContext, "Welcome", AUTO_STRING_LENGTH, 48, 15, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "to", AUTO_STRING_LENGTH, 48, 25, TRANSPARENT_TEXT);
    Graphics_drawStringCentered(&g_sContext, "ECE2049-C23!", AUTO_STRING_LENGTH, 48, 35, TRANSPARENT_TEXT);

    // Draw a box around everything because it looks nice
    Graphics_Rectangle box = {.xMin = 5, .xMax = 91, .yMin = 5, .yMax = 91 };
    Graphics_drawRectangle(&g_sContext, &box);

    // We are now done writing to the display.  However, if we stopped here, we would not
    // see any changes on the actual LCD.  This is because we need to send our changes
    // to the LCD, which then refreshes the display.
    // Since this is a slow operation, it is best to refresh (or "flush") only after
    // we are done drawing everything we need.
    Graphics_flushBuffer(&g_sContext);

    dispThree[0] = ' ';
    dispThree[2] = ' ';

    while (1)    // Forever loop
    {
        // Check if any keys have been pressed on the 3x4 keypad
        currKey = getKey();
        if (currKey == '*')
            BuzzerOn();
        if (currKey == '#')
            BuzzerOff();
        if ((currKey >= '0') && (currKey <= '9'))
            setLeds(currKey - 0x30);

        if (currKey)
        {
            dispThree[1] = currKey;
            // Draw the new character to the display
            Graphics_drawStringCentered(&g_sContext, dispThree, dispSz, 48, 55, OPAQUE_TEXT);

            // Refresh the display so it shows the new data
            Graphics_flushBuffer(&g_sContext);

            // wait awhile before clearing LEDs
            swDelay(1);
            setLeds(0);
        }

    }  // end while (1)
}

*/
void swDelay(char numLoops){
    // This function is a software delay. It performs
    // useless loops to waste a bit of time
    //
    // Input: numLoops = number of delay loops to execute
    // Output: none
    //
    // smj, ECE2049, 25 Aug 2013

    volatile unsigned int i,j;  // volatile to prevent removal in optimization
                                // by compiler. Functionally this is useless code

    for (j=0; j<numLoops; j++)
    {
        i = 50000 ;                 // SW Delay
        while (i > 0)               // could also have used while (i)
           i--;
    }
}


void setup(){
    P7SEL &= ~ (BIT0);   //bit 4 and 0 are 0
    P3SEL &= ~ (BIT6);   //bit 6 is 0
    //P2SEL &= ~ (BIT2);   //bit 2 is 0

    P7DIR &= ~ (BIT0);
    P3DIR &= ~ (BIT6);
    //P2DIR &= ~ (BIT2);

    P7REN |= (BIT0);
    P3REN |= (BIT6);
    //P2REN |= (BIT2);

    P7OUT |= (BIT0);
    P3OUT |= (BIT6);
    //P2OUT |= (BIT2);

}

int pressed(){
    int on = 0x00;
    int S1 = P7IN&BIT0;
    int S2 = P3IN & BIT6;

    if (S1 ==0){
        on = (on|BIT0);
    }
    if (S2 ==0){
           on = (on|BIT1);
       }
    return on;
}

