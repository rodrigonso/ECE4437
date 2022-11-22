/*
 * pid.c
 *
 *  Created on: Oct 26, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "pid.h"

bool send_data = false;
int data_count = 0;
MODBUS_PACKET data_ping;
MODBUS_PACKET data_pong;
MODBUS_PACKET* data_curr;
MODBUS_PACKET* data_prev;


void PID_Init(void)
{
    data_ping.mb.colon = ':';
    data_ping.mb.address = 1;
    data_ping.mb.checksum = 1;
    data_ping.mb.cr = '\r';
    data_ping.mb.lf = '\n';
    data_ping.data_raw[25] = '\0';

    data_pong.mb.colon = ':';
    data_pong.mb.address = 1;
    data_pong.mb.checksum = 1;
    data_pong.mb.cr = '\r';
    data_pong.mb.lf = '\n';
    data_pong.data_raw[25] = '\0';

    should_uturn = false;
    Bluetooth_Send("PID initialized!\r\n");
}


void PID_Run(UArg arg0, UArg arg1)
{
    while (1)
    {
        Semaphore_pend(PID_SEMA_0, BIOS_WAIT_FOREVER);

        if (should_uturn)
            PID_UTurn();
        else
            PID_Follow();

        Task_yield();
    }
}

void PID_Follow(void)
{
    Motor_Forward(MOTOR_LEFT);
    Motor_Forward(MOTOR_RIGHT);

    float P, I, D, PID, steering_val, I_prev = 0;

    pid_curr_error =  100 * ((float)PID_SETPOINT - Distance_GetDistanceRight()) / PID_SETPOINT;

    P = PID_KP * pid_curr_error;
    I = PID_KI * (I_prev + pid_curr_error * 0.05);
    D = PID_KD * (pid_curr_error - pid_prev_error) / 0.05;

    PID = (P + I + D);
    steering_val = fabs(PID);

    // Too far turn right
    if (pid_curr_error > 0)
        Motor_TurnRight(steering_val);

    // Too close turn left
    else
        Motor_TurnLeft(steering_val);

    pid_prev_error = pid_curr_error;
    I_prev = I;

    should_uturn = (Distance_GetDistanceFront() > UTURN_MAX);
}

void PID_SendData(UArg arg0, UArg arg1)
{
    while (1)
    {
        Semaphore_pend(PID_SEMA_1, BIOS_WAIT_FOREVER);
        if (Control_GetState() == SYSTEM_STOP || Control_GetSendData() == false) Task_yield();

        int d = abs(pid_curr_error / PID_SETPOINT * 255);
        if (data_count < 20)
        {
            LED_Disable(BLUE_LED);
            if (d > 255) d = 255;
            data_curr->mb.data[data_count++] = (char) d;
        }
        else
        {
            LED_Enable(BLUE_LED);
            data_prev = data_curr;
            if (data_curr = &data_pong) data_curr = &data_ping;
            else data_curr = &data_pong;

            data_count = 0;
            Bluetooth_Send(data_prev->data_raw);
            Bluetooth_Send("\r\n");
        }
    }
}


void PID_UTurn(void)
{
    Motor_UTurn();
    if (Distance_GetDistanceFront() < UTURN_MIN)
        should_uturn = false;
}



