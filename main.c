/*
 * File:   main.c
 * Author: Mike Peters
 * 1000750876
 *
 * Lab 6
 */

#include <stdio.h>
#include <stdlib.h>
#include <p24Hxxxx.h>
#include <peripheralversion.h>
#include <Generic.h>
#include "../EE3310_Lab06.X/include/chip_setup.h"
#include "../EE3310_Lab06.X/include/uart_config.h"



/*
 WORDS OF POWER

 * The configuration below sets up the chip configuration.
 * FBS:         Write to Boot Segment, No boot program to flash, No Boot RAM
 * FGS:         Program Memory not write protected, Code protect disabled
 * FOSCSEL:     Use Internal Fast RC, Device startup with selected oscillator source
 * FOSC:        OSC2 pin is digital I/O, No Primary Oscillator, Clock Switching Enabled
 *                Fail-Safe Clock Monitor disabled
 * FWDT:        Postscalar 1:8192, Prescalar 1:32, WDT is in Non-Window mode, WDT enabled by software
 * FPOR:        POR set for 128ms
 * FICD:        Use PGD1 for programming, JTAG Disabled
 */
_FBS(BWRP_WRPROTECT_OFF & BSS_NO_BOOT_CODE )
_FGS(GWRP_OFF & GCP_OFF)
_FOSCSEL( FNOSC_FRCPLL & IESO_OFF)
_FOSC(OSCIOFNC_ON & POSCMD_NONE & FCKSM_CSECMD)
_FWDT( WDTPOST_PS8192 & WDTPRE_PR32 & WINDIS_OFF & FWDTEN_OFF)
_FPOR( FPWRT_PWR128)
_FICD( ICS_PGD1 & JTAGEN_OFF)

/*
 * 
 */
_PROMPTSTATE PromptState = WAITING;

int main(int argc, char** argv) {
    int xVal, yVal;

    void Ludacris_Speed_GO(void);
    Ludacris_Speed_GO();

    UART1_Config();
    Timer1_Setup();
    Pin_Setup();
    Interrupt_Setup();

    printf("\nWe're gon-na to get you...\n");
    
    while(1)
    {
        switch (PromptState)
        {
            case GETXINPUT:
            case GETYINPUT:
                    if (PromptState == GETXINPUT)
                    {
                        if(!Prompted)
                        {
                           printf("x = ");
                           Prompted++;
                        }
                        if(RX_Done)
                        {
                           xVal = atoi(RX_Data);
                           PromptState = GETYINPUT;
                           Prompted = 0;
                           RX_Done = 0;
                           ClearString();
                        }
                    }
                    if (PromptState == GETYINPUT)
                    {
                        if(!Prompted)
                        {
                            printf("y = ");
                            Prompted++;
                        }
                       if(RX_Done)
                        {
                           yVal = atoi(RX_Data);
                           PromptState = CALCULATE;
                           Prompted = 0;
                           RX_Done = 0;
                           ClearString();
                        }
                    }
                    Prompted = 1;
                break;
            case CALCULATE:
                Calculate(xVal, yVal);
                printf("Press Enter to play again...");
                break;
            case WAITING:
                Nop();
                if(RX_Done)
                {
                    PromptState = RESET;
                    RX_Done = 0;
                }
                break;
            case RESET:
                Prompted = 0;
                T1CONbits.TON = 1;
                PromptState = WAITING;
        }
    }
    return (EXIT_SUCCESS);
}

inline void Ludacris_Speed_GO()
{
    //This code from Microchip Family Ref. 39 Oscillator(Part III)
    //Example 39-1
    //Configure PLL prescaler, PLL postscaler, PLL divisor
    PLLFBD = 41; // M = 43
    CLKDIVbits.PLLPOST = 0; // N2 = 2
    CLKDIVbits.PLLPRE = 0; // N1 = 2
    // Initiate Clock Switch to Internal FRC with PLL (NOSC = 0b001)
    __builtin_write_OSCCONH(0x01);
    __builtin_write_OSCCONL(0x01);
    // Wait for Clock switch to occur
    while (OSCCONbits.COSC != 0b001);
    // Wait for PLL to lock
    while(OSCCONbits.LOCK != 1) {};
    return;
}
