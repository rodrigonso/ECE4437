/*
 * bluetooth.h
 *
 *  Created on: Sep 26, 2022
 *      Author: Rodrigo Mascarenhas
 */

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
#include <ti/sysbios/knl/Semaphore.h>
#include <ti/sysbios/BIOS.h>

#include "../config.h"
#include "controllers/control.h"
#include "drivers/led.h"
#include "drivers/motor.h"
#include "drivers/light_sensor.h"

#ifndef DRIVERS_BLUETOOTH_H_
#define DRIVERS_BLUETOOTH_H_

extern Semaphore_Handle BLUETOOTH_SEMA_0;

// Functions
void Bluetooth_Init(void);
void Bluetooth_Send(char str[]);
void Bluetooth_SendInt(int);
void Bluetooth_IntHandler(void);
void Bluetooth_CommandHandler(UArg, UArg);
void Bluetooth_ProcessInput(void);
void Bluetooth_EraseBuffer(void);

#endif /* DRIVERS_BLUETOOTH_H_ */
