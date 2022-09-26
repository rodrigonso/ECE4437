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

#ifndef CONTROLLERS_BLUETOOTH_H_
#define CONTROLLERS_BLUETOOTH_H_

#define UART_BAUDRATE 115200

// Functions
int Bluetooth_Init(void (*callback)(char));
void Bluetooth_Send(const uint8_t *pui8Buffer, uint32_t ui32Count);
void Bluetooth_IntHandler(void);

// Variables
void (*interrupt_callback_ptr)(char);

#endif /* CONTROLLERS_BLUETOOTH_H_ */
