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
 *
 *
 *
 *
*/

void Motor_Init(void)
{
    speed_left = MIN_SPEED;
    speed_right = MIN_SPEED;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM1);             // Enables PWM1 peripheral.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_PWM0);             // Enables PWM0 Peripheral.
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOC);            // Enables Port C Peripheral.

    SysCtlPWMClockSet(SYSCTL_PWMDIV_64);                    // Sets the PWM clock configuration.

    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_7);     // Configures Port C pin 7 for use as a GPIO output.
    GPIOPinTypeGPIOOutput(GPIO_PORTC_BASE, GPIO_PIN_6);     // Configures Port C pin 6 for use as a GPIO output.

    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);           // Writes a value to Port C pin 7.
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);           // Writes a value to Port C pin 6.

    GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_5);            // Configures Port C pin 5 for use by the PWM peripheral.
    GPIOPinTypePWM(GPIO_PORTC_BASE, GPIO_PIN_4);            // Configures Port C pin 5 for use by the PWM peripheral.

    GPIOPinConfigure(GPIO_PC5_M0PWM7);                      // Configures the alternate function of a GPIO Port C pin 5.
    GPIOPinConfigure(GPIO_PC4_M0PWM6);                      // Configures the alternate function of a GPIO Port C pin 4.

    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN); //Configures a PWM generator.

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, PERIOD);  // Sets the period of a PWM generator.

    PWMGenEnable(PWM0_BASE, PWM_GEN_3);                     // Enables the timer/counter for a PWM generator block.

    Bluetooth_Send("Motor initialized!\r\n");
}


void Motor_Start(void)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true);         // Enables PWM 6 output.
    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);         // Enables PWM 7 output.
}

void Motor_Stop(void)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, false);         // Disables PWM 6 output.
    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, false);         // Disables PWM 7 output.
}

void Motor_Forward(int motor)
{
    if (motor == MOTOR_RIGHT) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);
    if (motor == MOTOR_LEFT) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);

    Motor_Start();
}

void Motor_Reverse(int motor)
{
    if (motor == MOTOR_RIGHT) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);
    if (motor == MOTOR_LEFT) GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);

    Motor_Start();
}

void Motor_SetSpeed(uint32_t speed, int motor)
{
    if (speed > MAX_SPEED) speed = MAX_SPEED;
    if (speed < MIN_SPEED) speed = MIN_SPEED;

    if (motor == MOTOR_RIGHT)  { PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, PERIOD * speed * 0.01); speed_right = speed;  }
    if (motor == MOTOR_LEFT)   { PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, PERIOD * speed * 0.01); speed_left = speed; }
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


