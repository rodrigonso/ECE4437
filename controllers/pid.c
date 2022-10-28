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
    Motor_SetSpeed(0);

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

void PID_Calculate(void)
{
    int32_t motor_speed = 0;
    float P, I, D, PID;

    pid_curr_error = PID_SETPOINT - Distance_GetDistanceRight();

    P = PID_KP * pid_curr_error;                    // Present error
    I = PID_KI * (pid_curr_error + pid_prev_error); // Past error
    D = PID_KD * (pid_curr_error - pid_prev_error); // Rate of error change

    PID = (P + I + D);
    pid_prev_error = pid_curr_error;

    motor_speed = (1000 - PID);

    Bluetooth_Send("Speed calculated!\r\n");
//    UARTprintf("Calculated motor speed: %d", motor_speed);
//    Motor_SetSpeed(motor_speed);
}





