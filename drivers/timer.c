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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER3);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_TIMER4); // used for race timer

    TimerConfigure(TIMER1_BASE, TIMER_CFG_PERIODIC);
    TimerConfigure(TIMER2_BASE, TIMER_CFG_PERIODIC);
    TimerConfigure(TIMER3_BASE, TIMER_CFG_PERIODIC);
    TimerConfigure(TIMER4_BASE, TIMER_CFG_ONE_SHOT_UP);

    ui32Period1 = (SysCtlClockGet() / 40);   // 100 ms
    ui32Period2 = (SysCtlClockGet() / 20);   // 50 ms
    ui32Period3 = (SysCtlClockGet() / 200);  // 5 ms

    TimerLoadSet(TIMER1_BASE, TIMER_A, ui32Period1);
    TimerLoadSet(TIMER2_BASE, TIMER_A, ui32Period2);
    TimerLoadSet(TIMER3_BASE, TIMER_A, ui32Period3);
    TimerLoadSet(TIMER4_BASE, TIMER_A, 0xFFFFFFFF);

    TimerControlTrigger(TIMER1_BASE, TIMER_A, true);
    TimerControlTrigger(TIMER2_BASE, TIMER_A, true);
    TimerControlTrigger(TIMER3_BASE, TIMER_A, true);

    TimerIntEnable(TIMER1_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntEnable(TIMER2_BASE, TIMER_TIMA_TIMEOUT);
    TimerIntEnable(TIMER3_BASE, TIMER_TIMA_TIMEOUT);

    TimerEnable(TIMER1_BASE, TIMER_A);
    TimerEnable(TIMER2_BASE, TIMER_A);
    TimerEnable(TIMER3_BASE, TIMER_A);

    Bluetooth_Send("Timer initialized!\r\n");
}

void Timer_IntHandler0(void)
{
    TimerIntClear(TIMER4_BASE, TIMER_TIMA_TIMEOUT);
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
}

void Timer_IntHandler3(void)
{
    TimerIntClear(TIMER3_BASE, TIMER_TIMA_TIMEOUT);
    int state = Control_GetState();

    if (state == SYSTEM_START)
        Semaphore_post(LIGHT_SEMA_0);
}

void Timer_RaceStart(void)
{
    TimerLoadSet(TIMER4_BASE, TIMER_A, 0xFFFFFFFF);
    HWREG(TIMER3_BASE + TIMER_O_TAV) = 0;
    TimerEnable(TIMER4_BASE, TIMER_A);
}

float Timer_RaceStop(void)
{
    TimerDisable(TIMER4_BASE, TIMER_A);
    TimerLoadSet(TIMER4_BASE, TIMER_A, 0xFFFFFFFF);
    HWREG(TIMER3_BASE + TIMER_O_TAV) = 0;

    return (float)((float)TimerValueGet(TIMER4_BASE, TIMER_A) / SysCtlClockGet());
}




