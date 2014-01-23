/*
 * File:   calc.c
 * Author: Mike Peters
 * 1000750876
 *
 * Lab 6
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include "../include/chip_setup.h"

volatile int Index = 0;
char RX_Data[10];
unsigned short Prompted = 0;     //Flag to idicate that the user has been prompted
                        //to enter a value.

unsigned short RX_Done = 0;


void ClearString(void)
{
    int i;
    Index = 0;  //reset array index
        
    for (i=0; i<10; i++)
    {
        RX_Data[i] = '\0';
    }
}
void Calculate(int x, int y)
{
    int z;
        z = x + y;
        printf("%d + %d = %d \n", x, y, z);
        PromptState = WAITING;
    return;
}

void __attribute__((interrupt, auto_psv)) _ISR _U1RXInterrupt(void)
{
    _U1RXIF = 0;
    char received;
    received = U1RXREG;
    /*
     * Only fill the RX string array when a 0-9 is received and when the array
     * is not full.
     */
    if(((received >= '0') && (received <= '9')) && (Index < 10))
    {
            RX_Data[Index] = received;          //put received char into array
            U1TXREG = received;                 //echo rec'd char to screen
            Index++;
    }
    if(received == 0x0d)
    {
        U1TXREG = 0x0d;
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        Nop();
        U1TXREG = 0x0a;
        RX_Done = 1;
    }
    return;
}





