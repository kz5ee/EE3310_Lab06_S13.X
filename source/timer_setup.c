/*
 * File:   timer_setup.c
 * Author: Mike Peters
 * 1000750876
 *
 * Lab 5
 */

#include <timer.h>
#include <stdio.h>
#include "../include/chip_setup.h"

volatile short INT_Counter = 0;
short i = 0;
void Timer1_Setup(void)
{
    OpenTimer1(
            T1_ON &
            T1_IDLE_CON &       
            T1_GATE_OFF &
            T1_PS_1_256 &
            T1_SYNC_EXT_OFF &
            T1_SOURCE_INT,
            0x9897);

    ConfigIntTimer1(
            T1_INT_PRIOR_3 &
            T1_INT_ON
                    );

    return;
}

void __attribute__((interrupt,auto_psv)) _ISR _T1Interrupt(void)
{
    _T1IF = 0;
    char dummy;
    if((++INT_Counter % 20) == 0)
    {
       PromptState = GETXINPUT;
       T1CONbits.TON = 0;
       _U1RXIE = 1;
    }
    dummy = U1RXREG;
    return;
}