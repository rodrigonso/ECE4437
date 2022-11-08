/*
 * control.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Rodrigo Mascarenhas
 */
#include "control.h"

int system_state;

void Control_Init(void)
{
    system_state = SYSTEM_STOP;
    LED_Enable(RED_LED);
    Bluetooth_Send("Control initialized!\r\n");
}

void Control_Start(void)
{
    LED_Disable(RED_LED);
    system_state = SYSTEM_START;
    Motor_Start();
    Bluetooth_Send("System Started!\r\n");
    LED_Enable(GREEN_LED);
}

void Control_Stop(void)
{
    LED_Disable(GREEN_LED);
    system_state = SYSTEM_STOP;
    Motor_Stop();
    Bluetooth_Send("System Stopped!\r\n");
    LED_Enable(RED_LED);
}

void Control_SetState(int state)
{
    if (state == SYSTEM_STOP) Control_Stop();
    if (state == SYSTEM_START) Control_Start();
}

int Control_GetState(void)
{
    return system_state;
}
