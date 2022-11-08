/*
 * led.h
 *
 *  Created on: Oct 4, 2022
 *      Author: Rodrigo Mascarenhas
 */

#ifndef DRIVERS_LED_H_
#define DRIVERS_LED_H_

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/gpio.h"
#include "driverlib/sysctl.h"

#include "drivers/bluetooth.h"

void LED_Init(void);
void LED_Toggle(uint32_t);
void LED_Enable(int);
void LED_Disable(int);

enum LEDS
{
    RED_LED,
    GREEN_LED,
    BLUE_LED
};

#endif /* DRIVERS_LED_H_ */
