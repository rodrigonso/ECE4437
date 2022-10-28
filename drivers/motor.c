/*
 * motor.c
 *
 *  Created on: Oct 17, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "motor.h"

void Motor_Init(void)
{
    is_motor_enabled = false;
    duty_cycle = 100;                                        // Default motors duty speed of 10% out of 100%

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

    pwm_clk = SysCtlClockGet() / 64;                        // A fraction of the PWM clock.
    val_load = (pwm_clk / 100) - 1;                         // Gets the period of PWM generator, measured in clock ticks.

    PWMGenConfigure(PWM0_BASE, PWM_GEN_3, PWM_GEN_MODE_DOWN); //Configures a PWM generator.

    PWMGenPeriodSet(PWM0_BASE, PWM_GEN_3, val_load);  // Sets the period of a PWM generator.

    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, duty_cycle * val_load / 100); // Sets the pulse width for the PWM 6 output.
    PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, duty_cycle * val_load / 100); // Sets the pulse width for the PWM 7 output.

    PWMGenEnable(PWM0_BASE, PWM_GEN_3);                     // Enables the timer/counter for a PWM generator block.

//    UARTprintf("Motor intialized\r\n");
    Bluetooth_Send("Motor initialized!\r\n");
}


void Motor_Start(UArg arg0, UArg arg1)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, true);         // Enables PWM 6 output.
    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, true);         // Enables PWM 7 output.

    is_motor_enabled = true;
}

void Motor_Stop(UArg arg0, UArg arg1)
{
    PWMOutputState(PWM0_BASE, PWM_OUT_6_BIT, false);         // Disables PWM 6 output.
    PWMOutputState(PWM0_BASE, PWM_OUT_7_BIT, false);         // Disables PWM 7 output.

    is_motor_enabled = false;
}

void Motor_Forward(UArg arg0, UArg arg1)
{
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, 0);           // Writes a value to Port C pin 6.
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, 0);           // Writes a value to Port C pin 7.

    Motor_Start(0, 0);                      // This function enables both motors to move.
}

void Motor_Reverse(UArg arg0, UArg arg1)
{
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_7, GPIO_PIN_7);  // Reverses the direction of the right motor.
    GPIOPinWrite(GPIO_PORTC_BASE, GPIO_PIN_6, GPIO_PIN_6);  // Reverses the direction of the left motor.

    Motor_Start(0, 0);                      // This function enables both motors to move.
}

bool Motor_IsMotorEnabled(void)
{
    return is_motor_enabled;
}

void Motor_SetSpeed(int32_t new_duty_cycle)
{
    if (new_duty_cycle > MAX_DUTY_CYCLE) new_duty_cycle = MAX_DUTY_CYCLE;
    if (new_duty_cycle < MIN_DUTY_CYCLE) new_duty_cycle = MIN_DUTY_CYCLE;

    duty_cycle = new_duty_cycle;

    if (new_duty_cycle == 0 && Motor_IsMotorEnabled())
    {
        Motor_Stop(0, 0);
        return;
    }
    else if (new_duty_cycle > 0 && !Motor_IsMotorEnabled())
    {
        Motor_Start(0, 0);
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_7, new_duty_cycle * val_load / 100); // Sets the pulse width for the PWM 7 output.
        PWMPulseWidthSet(PWM0_BASE, PWM_OUT_6, new_duty_cycle * val_load / 100); // Sets the pulse width for the PWM 6 output.
    }
}

int32_t Motor_GetSpeed(void)
{
    return duty_cycle;
}




