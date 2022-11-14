/*
 * motor.c
 *
 *  Created on: Oct 17, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "motor.h"

/*
 *  Left motor  -> PWM_OUT_6
 *  Right motor -> PWM_OUT_7
*/

void Motor_Init(void)
{
    speed_left = MIN_SPEED;
    speed_right = MIN_SPEED;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);

    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);

    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);

    GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_5);
    GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_4);

    GPIOPinConfigure(GPIO_PC5_M0PWM7);
    GPIOPinConfigure(GPIO_PC4_M0PWM6);

    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN);

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, PERIOD);

    PWMGenEnable(PWM0_BASE, PWM_GEN_3);

    Bluetooth_Send("Motor initialized!\r\n");
}


void Motor_Start(void)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true);
    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);
}

void Motor_Stop(void)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, false);
    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, false);
}

void Motor_Forward(int motor)
{
    if (motor == MOTOR_LEFT) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);
    if (motor == MOTOR_RIGHT) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);

    Motor_Start();
}

void Motor_Reverse(int motor)
{
    if (motor == MOTOR_LEFT) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);
    if (motor == MOTOR_RIGHT) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);

    Motor_Start();
}

void Motor_SetSpeed(uint32_t speed, int motor)
{
    if (speed > MAX_SPEED) speed = MAX_SPEED;
    if (speed < MIN_SPEED) speed = MIN_SPEED;

    if (motor == MOTOR_LEFT)   { PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, PERIOD * speed * 0.01); speed_left = speed; }
    if (motor == MOTOR_RIGHT)  { PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, PERIOD * speed * 0.01); speed_right = speed;  }
}

uint32_t Motor_GetSpeed(int motor)
{
    if (motor == MOTOR_RIGHT) return speed_right;
    if (motor == MOTOR_LEFT) return speed_left;

    else return 0;
}

void Motor_TurnLeft(int steering)
{
    if (steering > MAX_STEERING) steering = MAX_STEERING;

    // Left motor
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, (int)(PERIOD * (MAX_SPEED - steering) * 0.01));

    // Right motor
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, (int)(PERIOD * MAX_SPEED * 0.01));
}

void Motor_TurnRight(int steering)
{
    if (steering > MAX_STEERING) steering = MAX_STEERING;

    // Left motor
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, (int)(PERIOD * MAX_SPEED * 0.01));

    // Right motor
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, (int)(PERIOD * (MAX_SPEED - steering) * 0.01));
}

void Motor_UTurn(void)
{
    Motor_Reverse(MOTOR_LEFT);
    Motor_Forward(MOTOR_RIGHT);
    Motor_SetSpeed(MAX_SPEED, MOTOR_LEFT);
    Motor_SetSpeed(MAX_SPEED, MOTOR_RIGHT);
}


