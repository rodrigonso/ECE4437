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

#define PID_SETPOINT      1600
#define PID_KP            2.0
#define PID_KI            0.1
#define PID_KD            0.09

#define UTURN_MAX         2600
#define UTURN_MIN         1000

extern Semaphore_Handle PID_SEMA_0;
extern Semaphore_Handle PID_SEMA_1;

float pid_curr_error, pid_prev_error;
uint32_t motor_speed_left, motor_speed_right;
bool should_uturn;

typedef struct {
    char colon;
    char address;
    char data[20];
    char checksum;
    char cr;
    char lf;
} MODBUS_DATA;

typedef union {
    char data_raw[26];
    MODBUS_DATA mb;
} MODBUS_PACKET;

void PID_Init(void);
void PID_Follow(void);
void PID_Run(UArg, UArg);
void PID_SendData(UArg, UArg);
void PID_Print(void);
void PID_UTurn(void);

#endif /* CONTROLLERS_PID_H_ */
