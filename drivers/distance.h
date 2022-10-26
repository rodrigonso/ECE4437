/*
 * distance.h
 *
 *  Created on: Oct 7, 2022
 *      Author: Rodrigo Mascarenhas
 */

#ifndef DRIVERS_DISTANCE_H_
#define DRIVERS_DISTANCE_H_

#include <stdint.h>
#include <stdbool.h>
#include <math.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include <driverlib/adc.h>
#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/knl/Task.h>
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/BIOS.h>
#include <ti/sysbios/hal/Hwi.h>

#include "drivers/timer.h"

#include "led.h"
#include "../config.h"

uint32_t distance_front;
uint32_t distance_right;

void Distance_Init(void);
void Distance_Print(void);
int32_t Distance_GetDistanceFront(void);
int32_t Distance_GetDistanceRight(void);


#endif /* DRIVERS_DISTANCE_H_ */
