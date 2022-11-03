/*
 * pid.c
 *
 *  Created on: Oct 26, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "pid.h"

void PID_Init(void)
{
    Motor_Forward(0, 0);
    Motor_SetSpeed(1000, MOTOR_RIGHT);
    Motor_SetSpeed(1000, MOTOR_LEFT);
//    UARTprintf("PID controller intitialized!\r\n");
    Bluetooth_Send("PID controller initialized!\r\n");
}


void PID_Run(UArg arg0, UArg arg1)
{
    while (1)
    {
        Semaphore_pend(PID_SEMA_0, BIOS_WAIT_FOREVER);
//        UARTprintf("SWI called\r\n");
        Bluetooth_Send("PID running...");
        PID_Calculate();
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
    Task_yield();
}

void PID_Calculate(void)
{
    float P, I, D, PID;

    pid_curr_error = PID_SETPOINT - Distance_GetDistanceFront();

    P = PID_KP * pid_curr_error;                    // Present error
    I = PID_KI * (pid_curr_error + pid_prev_error); // Past error
    D = PID_KD * (pid_curr_error - pid_prev_error); // Rate of error change

    pid_prev_error = pid_curr_error;
    PID = (P + I + D);

    motor_speed_left = (1000 - PID);

    Bluetooth_Send("Speed calculated!\r\n");
    Motor_SetSpeed(motor_speed_left, MOTOR_LEFT);
//    Motor_SetSpeed(speed_right, MOTOR_RIGHT);

    PID_Print();
//    UARTprintf("Calculated motor speed: %d", motor_speed);
}





