/*
 * pid.c
 *
 *  Created on: Oct 26, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "pid.h"

void PID_Init(void)
{
    Motor_Forward();
    Motor_SetSpeed(0);

    // Instantiation
    Swi_Params_init(&PID_SWI_0_P);
    PID_SWI_0_P.arg0 = 0;
    PID_SWI_0_P.arg1 = 0;
    PID_SWI_0_P.priority = 2;
    PID_SWI_0 = Swi_create((Swi_FuncPtr)PID_SwiHandler, &PID_SWI_0_P, 0);

    UARTprintf("PID controller intitialized!\r\n");
}


void PID_SwiHandler(void)
{
    UARTprintf("SWI called\r\n");
    PID_Calculate();
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

    UARTprintf("Calculated motor speed: %d", motor_speed);
    Motor_SetSpeed(motor_speed);
}





