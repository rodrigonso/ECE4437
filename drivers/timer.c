/*
 * timer.c
 *
 *  Created on: Oct 17, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "timer.h"

void Timer_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER2);

    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);

    ui32Period1 = (SysCtlClockGet() / 40); // 100 ms
    ui32Period2 = (SysCtlClockGet() / 20); // 50 ms

    TimerLoadSet(TIMER1_BASE, TIMER_A, ui32Period1);
    TimerLoadSet(TIMER2_BASE, TIMER_A, ui32Period2);

    TimerControlTrigger(TIMER1_BASE, TIMER_A, true);
    TimerControlTrigger(TIMER2_BASE, TIMER_A, true);

    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);

    TimerEnable(TIMER1_BASE, TIMER_A);
    TimerEnable(TIMER2_BASE, TIMER_A);

    Bluetooth_Send("Timer initialized!\r\n");
}

void Timer_IntHandler1(void)
{
    TimerIntClear(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    int state = Control_GetState();

    if (state == SYSTEM_START)
        Semaphore_post(PID_SEMA_1);
}

void Timer_IntHandler2(void)
{
    TimerIntClear(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    int state = Control_GetState();

    if (state == SYSTEM_START)
        Semaphore_post(PID_SEMA_0);
    else if (state == SYSTEM_START || state == SYSTEM_TEST)
        Semaphore_post(LIGHT_SEMA_0);
}





