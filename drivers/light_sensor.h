/*
 * light_sensor.h
 *
 *  Created on: Nov 6, 2022
 *      Author: Rodrigo Mascarenhas
 */

#ifndef DRIVERS_LIGHT_SENSOR_H_
#define DRIVERS_LIGHT_SENSOR_H_

#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include <ti/sysbios/knl/Semaphore.h>

#include "drivers/bluetooth.h"
#include "controllers/control.h"

#define LINE_COUNT_MIN 5
#define LINE_COUNT_MAX 20
#define LIGHT_SENSOR_THRESHOLD 3500

extern Semaphore_Handle LIGHT_SEMA_0;

enum LINES
{
    THIN_LINE,
    THICK_LINE
};

void LightSensor_Init(void);
void LightSensor_Read(UArg arg0, UArg arg1);
int LightSensor_CheckLine(int);

#endif /* DRIVERS_LIGHT_SENSOR_H_ */
