/*
 * bluetooth.h
 *
 *  Created on: Sep 26, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include <stdint.h>
#include <stdbool.h>
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
#include "led.h"

#ifndef DRIVERS_BLUETOOTH_H_
#define DRIVERS_BLUETOOTH_H_

// Functions
void Bluetooth_Init(void);
void Bluetooth_Send(const uint8_t *pui8Buffer, uint32_t ui32Count);
void Bluetooth_IntHandler(void);
void Bluetooth_ProcessInput(void);

#endif /* DRIVERS_BLUETOOTH_H_ */
