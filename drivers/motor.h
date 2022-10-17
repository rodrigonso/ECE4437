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

#define MAX_DUTY_CYCLE 100
#define MIN_DUTY_CYCLE 0

uint16_t duty_cycle;
uint32_t val_load, pwm_clk;

void Motor_Init();
void Motor_Start(void);
void Motor_Stop(void);
void Motor_Forward(void);
void Motor_Reverse(void);
void Motor_SetSpeed(int32_t speed);
int32_t Motor_GetSpeed(void);


#endif /* DRIVERS_MOTOR_H_ */
