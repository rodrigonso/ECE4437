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
#include <stdlib.h>

#include "../drivers/motor.h"
#include "../drivers/distance.h"
#include "../drivers/bluetooth.h"

#define PID_SETPOINT      2600
#define PID_KP            0.05
#define PID_KI            0.02
#define PID_KD            0.1

extern Semaphore_Handle PID_SEMA_0;

float pid_curr_error, pid_prev_error;
uint32_t motor_speed_left;

void PID_Init(void);
void PID_Calculate(void);
void PID_Run(UArg, UArg);
void PID_Print(void);

#endif /* CONTROLLERS_PID_H_ */
