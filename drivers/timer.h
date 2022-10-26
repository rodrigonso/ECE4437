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

#include <ti/sysbios/knl/Swi.h>
#include <ti/sysbios/hal/Hwi.h>

#include "controllers/pid.h"

uint32_t ui32Period;

void Timer_Init(void);
void Timer_IntHandler(void);

Hwi_Handle TIMER_HWI_0;
Hwi_Params TIMER_HWI_0_P;

#endif /* DRIVERS_TIMER_H_ */
