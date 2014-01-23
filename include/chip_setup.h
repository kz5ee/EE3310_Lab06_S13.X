/*
 * File:   chip_setup.h
 * Author: Mike Peters
 * 1000750876
 *
 * Lab 6
 */

#ifndef CHIP_SETUP_H
#define	CHIP_SETUP_H

#ifdef	__cplusplus
extern "C" {
#endif

#include <p24hxxxx.h>

    extern unsigned short Prompted, RX_Done;
    extern char RX_Data[10];

    extern void Timer1_Setup(void);
    extern void Pin_Setup(void);
    extern void Interrupt_Setup(void);
    extern void Calculate(int, int);
    extern void ClearString(void);

    typedef enum{
        WAITING = 0,
                GETXINPUT,
                GETYINPUT,
                CALCULATE,
                RESET
    }_PROMPTSTATE;

    extern _PROMPTSTATE PromptState;


#ifdef	__cplusplus
}
#endif

#endif	/* CHIP_SETUP_H */

