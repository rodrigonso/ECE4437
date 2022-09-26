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

#define UART_BAUDRATE 115200

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



void UART_IntHandler(void)
{
    uint32_t ui32Status;

    // Get the interrrupt status.
    ui32Status = UARTIntStatus(UART5_BASE, true);

    // Clear the asserted interrupts.
    UARTIntClear(UART5_BASE, ui32Status);

    // Loop while there are characters in the receive FIFO.
    while(UARTCharsAvail(UART5_BASE))
    {

        // Read the next character from the UART and write it back to the UART.
        UARTCharPutNonBlocking(UART5_BASE, UARTCharGetNonBlocking(UART5_BASE));

        // Blink the LED to show a character transfer is occuring.
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, GPIO_PIN_2);

        // Delay for 1 millisecond.  Each SysCtlDelay is about 3 clocks.
        SysCtlDelay(SysCtlClockGet() / (1000 * 3));

        // Turn off the LED
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_2, 0);

    }
}

void UART_Send(const uint8_t *pui8Buffer, uint32_t ui32Count)
{

    // Loop while there are more characters to send.
    while(ui32Count--)
    {
        // Write the next character to the UART.
        UARTCharPutNonBlocking(UART5_BASE, *pui8Buffer++);
    }
}

void UART_Init()
{
    IntMasterEnable();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // Port used by UART5
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5); // UART5 module
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Port used by LEDs

    GPIOPinConfigure(GPIO_PE4_U5RX);
    GPIOPinConfigure(GPIO_PE5_U5TX);
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);

    UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), UART_BAUDRATE, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    UARTEnable(UART5_BASE);

    IntEnable(INT_UART5);
    UARTIntEnable(UART5_BASE, UART_INT_RX | UART_INT_RT);
}

int main(void)
{
    // Set the clocking to run directly from the crystal.
    SysCtlClockSet(SYSCTL_SYSDIV_1 | SYSCTL_USE_OSC | SYSCTL_OSC_MAIN | SYSCTL_XTAL_16MHZ);

    UART_Init();
    UART_Send((uint8_t *)"\033[2JEnter text: ", 16);

    while (1)
    {
        // Do nothing
    }

}
