//*****************************************************************************
//
// uart_echo.c - Example for reading data from and writing data to the UART in
//               an interrupt driven fashion.
//
// Copyright (c) 2012-2017 Texas Instruments Incorporated.  All rights reserved.
// Software License Agreement
// 
// Texas Instruments (TI) is supplying this software for use solely and
// exclusively on TI's microcontroller products. The software is owned by
// TI and/or its suppliers, and is protected under applicable copyright
// laws. You may not combine this software with "viral" open-source
// software in order to form a larger program.
// 
// THIS SOFTWARE IS PROVIDED "AS IS" AND WITH ALL FAULTS.
// NO WARRANTIES, WHETHER EXPRESS, IMPLIED OR STATUTORY, INCLUDING, BUT
// NOT LIMITED TO, IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE APPLY TO THIS SOFTWARE. TI SHALL NOT, UNDER ANY
// CIRCUMSTANCES, BE LIABLE FOR SPECIAL, INCIDENTAL, OR CONSEQUENTIAL
// DAMAGES, FOR ANY REASON WHATSOEVER.
// 
// This is part of revision 2.1.4.178 of the EK-TM4C123GXL Firmware Package.
//
//*****************************************************************************

#include <stdint.h>
#include <stdbool.h>
#include "inc/hw_ints.h"
#include "inc/hw_memmap.h"
#include "driverlib/debug.h"
#include "driverlib/fpu.h"
#include "driverlib/gpio.h"
#include "driverlib/interrupt.h"
#include "driverlib/pin_map.h"
#include "driverlib/rom.h"
#include "driverlib/sysctl.h"
#include "driverlib/uart.h"

#include "controllers/bluetooth.h"

//*****************************************************************************
//
//! \addtogroup example_list
//! <h1>UART Echo (uart_echo)</h1>
//!
//! This example application utilizes the UART to echo text.  The first UART
//! (connected to the USB debug virtual serial port on the evaluation board)
//! will be configured in 115,200 baud, 8-n-1 mode.  All characters received on
//! the UART are transmitted back to the UART.
//
//*****************************************************************************

//*****************************************************************************
//
// The error routine that is called if the driver library encounters an error.
//
//*****************************************************************************
#ifdef DEBUG
void
__error__(char *pcFilename, uint32_t ui32Line)
{
}
#endif

uint8_t RED_LED_STATE   = 0x0;
uint8_t BLUE_LED_STATE  = 0x0;
uint8_t GREEN_LED_STATE = 0x0;

void process_input(char ch)
{
    uint8_t LED_PIN    = 0x0;
    uint8_t *LED_STATE = &RED_LED_STATE;

    if (ch == 'r') { LED_PIN = GPIO_PIN_1; LED_STATE = &RED_LED_STATE;   }
    if (ch == 'g') { LED_PIN = GPIO_PIN_3; LED_STATE = &GREEN_LED_STATE; }
    if (ch == 'b') { LED_PIN = GPIO_PIN_2; LED_STATE = &BLUE_LED_STATE;  }

    bool is_led_on = *(LED_STATE) > 0x0;

    GPIOPinWrite(GPIO_PORTF_BASE, LED_PIN, (is_led_on ? 0x0 : LED_PIN));
    *LED_STATE = is_led_on ? 0x0: LED_PIN;
}

int main(void)
{
    // Set the clocking to run directly from the crystal.
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    Bluetooth_Init(&process_input);
    Bluetooth_Send((uint8_t *)"\033[2JEnter text: ", 16);

    while (1)
    {
        // Do nothing
    }

}
