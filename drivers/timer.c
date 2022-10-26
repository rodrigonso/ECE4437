/*
 * timer.c
 *
 *  Created on: Oct 17, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "timer.h"

void Timer_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);           // enable Timer 2 periph clks
    TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);        // cfg Timer 2 mode - periodic

    ui32Period = (SysCtlClockGet() /2);                     // period = CPU clk div 2 (500ms) (40M/2)*(1/40000000) = 0.5)*
    TimerLoadSet(TIMER2_BASE, TIMER_A, ui32Period);         // set Timer 2 period
    TimerControlTrigger(TIMER2_BASE, TIMER_A, true);

    TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);        // enables Timer 2 to interrupt CPU
    TimerEnable(TIMER2_BASE, TIMER_A);                      // enable Timer 2

    Hwi_Params_init(&TIMER_HWI_0_P);
    TIMER_HWI_0_P.arg = 5;
    TIMER_HWI_0_P.priority = 1;
    TIMER_HWI_0 = Hwi_create(39, (Hwi_FuncPtr)Timer_IntHandler, &TIMER_HWI_0_P, 0);

    UARTprintf("Timer initialized!\r\n");
}

void Timer_IntHandler(void)
{
    UARTprintf("Timer called\r\n");
    TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    Swi_post(PID_SWI_0);
}




