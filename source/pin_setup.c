

#include <pps.h>
#include "../include/chip_setup.h"

inline void Interrupt_Setup(void)
{
    _INT1IE = 1;    //Enable External Interrupt INT1

    _INT1IP = 4;    //Set INT1 interrupt priority to 4

    _INT1IF = 0;    //Clear INT1 interrupt flag

    _INT1EP = 0;    //Set INT1 interrupt on positive edge
}

inline void Pin_Setup(void)
{
    TRISBbits.TRISB11 = 1;

    /*Set RB11 as external interrupt INT1*/
    PPSInput(PPS_INT1, PPS_RP11);
}

void __attribute__((interrupt,auto_psv)) _ISR _INT1Interrupt( void)
{
    _INT1IF = 0;
    U1TXREG = 0xa5;
    
    return;
}