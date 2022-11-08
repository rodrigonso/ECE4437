/*
 * pid.c
 *
 *  Created on: Oct 26, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "pid.h"

void PID_Init(void)
{
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

void PID_Print(void)
{
    char *out = (char*)malloc(8 * sizeof(char));
    if (out == NULL) return;
    uint32_t dist = Distance_GetDistanceRight();
    sprintf(out, "Distance1: %d, Distance2: %d  |  SpeedL: %d\r\n", dist, Distance_GetDistanceFront(), motor_speed_left);
    Bluetooth_Send(out);
    free(out);
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

void PID_UTurn(void)
{
    Motor_UTurn();
    if (Distance_GetDistanceFront() < UTURN_MIN)
        should_uturn = false;
}






