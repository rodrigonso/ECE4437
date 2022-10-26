/*
 * pid.h
 *
 *  Created on: Oct 26, 2022
 *      Author: Rodrigo Mascarenhas
 */

#ifndef CONTROLLERS_PID_H_
#define CONTROLLERS_PID_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Hwi.h>

#include "../drivers/motor.h"
#include "../drivers/distance.h"

#define PID_SETPOINT      1600
#define PID_KP            0.25
#define PID_KI            0.04
#define PID_KD            0.01

float pid_curr_error, pid_prev_error;

void PID_Init(void);
void PID_Calculate(void);
void PID_SwiHandler(void);

Swi_Handle PID_SWI_0;
Swi_Params PID_SWI_0_P;

#endif /* CONTROLLERS_PID_H_ */
