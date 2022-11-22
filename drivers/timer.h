/*
 * timer.h
 *
 *  Created on: Oct 17, 2022
 *      Author: Rodrigo Mascarenhas
 */

#ifndef DRIVERS_TIMER_H_
#define DRIVERS_TIMER_H_

#include <stdbool.h>
#include <stdint.h>
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/systick.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"
#include "inc/hw_types.h"
#include "inc/hw_ints.h"
#include "driverlib/timer.h"
#include "inc/hw_timer.h"

#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/hal/Hwi.h>

#include "controllers/pid.h"
#include "drivers/bluetooth.h"

extern Semaphore_Handle PID_SEMA_0;
extern Semaphore_Handle LIGHT_SEMA_0;

uint32_t ui32Period1, ui32Period2, ui32Period3;

void Timer_Init(void);
void Timer_IntHandler(void);
void Timer_RaceStart(void);
float Timer_RaceStop(void);

#endif /* DRIVERS_TIMER_H_ */
