/*
 * console.h
 *
 *  Created on: Oct 8, 2022
 *      Author: Rodrigo Mascarenhas
 */

#ifndef DRIVERS_CONSOLE_H_
#define DRIVERS_CONSOLE_H_

#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <string.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"
#include "utils/uartstdio.h"

#include "../config.h"


void Console_Init(void);
void Console_Send(const uint8_t *pui8Buffer, uint32_t ui32Count);
void Console_SendInt(const uint8_t data);
void Console_Print(char str[]);


#endif /* DRIVERS_CONSOLE_H_ */
