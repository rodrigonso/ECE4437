/*
 * control.c
 *
 *  Created on: Nov 4, 2022
 *      Author: Rodrigo Mascarenhas
 */
#include "control.h"

int system_state;
bool should_send_data = false;

void Control_Init(void)
{
    system_state = SYSTEM_STOP;
    LED_Enable(RED_LED);
    Bluetooth_Send("Control initialized!\r\n");
}

void Control_Start(void)
{
    LED_Disable(RED_LED);
    LED_Disable(BLUE_LED);
    system_state = SYSTEM_START;
    Motor_Start();
    Bluetooth_Send("System Started!\r\n");

    Timer_RaceStart();

    LED_Enable(GREEN_LED);
}

void Control_Stop(void)
{
    LED_Disable(GREEN_LED);
    LED_Disable(BLUE_LED);
    system_state = SYSTEM_STOP;
    Motor_Stop();
    Bluetooth_Send("System Stopped!\r\n");

    float running_time = Timer_RaceStop();
    Bluetooth_Send("Race time: ");
    Bluetooth_SendFloat(running_time);
    Bluetooth_Send(" seconds");

    LED_Enable(RED_LED);
}

void Control_Test(void)
{
    LED_Disable(GREEN_LED);
    LED_Disable(RED_LED);
    system_state = SYSTEM_TEST;
    Motor_Stop();
    Bluetooth_Send("System in Testing mode!\r\n");
    LED_Enable(BLUE_LED);
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

bool Control_GetSendData(void)
{
    return should_send_data;
}

void Control_SetSendData(bool val)
{
    should_send_data = val;
}
