/*
 * motor.h
 *
 *  Created on: Oct 17, 2022
 *      Author: Rodrigo Mascarenhas
 */

#ifndef DRIVERS_MOTOR_H_
#define DRIVERS_MOTOR_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <inc/hw_memmap.h>
#include <driverlib/sysctl.h>
#include <driverlib/gpio.h>
#include <driverlib/pin_map.h>
#include <driverlib/pwm.h>
#include "driverlib/uart.h"
#include "inc/hw_types.h"
#include "inc/hw_gpio.h"
#include "inc/hw_memmap.h"
#include "utils/uartstdio.h"
#include <ti/sysbios/knl/Task.h>

#include "drivers/bluetooth.h"

#define MAX_STEERING 99
#define MAX_SPEED 100
#define MIN_SPEED 1
#define PERIOD 2000

enum MOTORS
{
    MOTOR_LEFT,
    MOTOR_RIGHT,
};

uint32_t speed_right, speed_left;

void Motor_Init(void);
void Motor_Start(void);
void Motor_Stop(void);
void Motor_Forward(int);
void Motor_Reverse(int);
void Motor_SetSpeed(uint32_t, int);
void Motor_TurnLeft(int);
void Motor_TurnRight(int);
void Motor_UTurn(void);
bool Motor_IsMotorEnabled(void);
uint32_t Motor_GetSpeed(int);


#endif /* DRIVERS_MOTOR_H_ */
