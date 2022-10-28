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

#define MAX_DUTY_CYCLE 1000
#define MIN_DUTY_CYCLE 0

uint16_t duty_cycle;
uint32_t val_load, pwm_clk;
bool is_motor_enabled;

void Motor_Init();
void Motor_Start(UArg, UArg);
void Motor_Stop(UArg, UArg);
void Motor_Forward(UArg, UArg);
void Motor_Reverse(UArg, UArg);
void Motor_SetSpeed(int32_t speed);
bool Motor_IsMotorEnabled(void);
int32_t Motor_GetSpeed(void);


#endif /* DRIVERS_MOTOR_H_ */
