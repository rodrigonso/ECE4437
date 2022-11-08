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

    ui32Period = (SysCtlClockGet() / 20);                     // period = CPU clk div 2 (500ms) (40M/2)*(1/40000000) = 0.5)*
    TimerLoadSet(TIMER2_BASE, TIMER_A, ui32Period);         // set Timer 2 period
    TimerControlTrigger(TIMER2_BASE, TIMER_A, true);

    TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);        // enables Timer 2 to interrupt CPU
    TimerEnable(TIMER2_BASE, TIMER_A);                      // enable Timer 2

//    UARTprintf("Timer initialized!\r\n");
    Bluetooth_Send("Timer initialized!\r\n");
}

void Timer_IntHandler(void)
{
    TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    if (Control_GetState() == SYSTEM_START)
        Semaphore_post(PID_SEMA_0);
}




