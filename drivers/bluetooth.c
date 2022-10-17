/*
 * bluetooth.c
 *
 *  Created on: Sep 26, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "../drivers/bluetooth.h"

void Bluetooth_IntHandler(void)
{
    uint32_t ui32Status;

    // Get the interrrupt status.
    ui32Status = UARTIntStatus(UART5_BASE, true);

    // Clear the asserted interrupts.
    UARTIntClear(UART5_BASE, ui32Status);
    // TODO: Post swi
}

void Bluetooth_Send(const uint8_t *pui8Buffer, uint32_t ui32Count)
{

    // Loop while there are more characters to send.
    while(ui32Count--)
    {
        // Write the next character to the UART.
        UARTCharPutNonBlocking(UART5_BASE, *pui8Buffer++);
    }
}

void Bluetooth_Read(void)
{
    while(UARTCharsAvail(UART5_BASE))
       {
           char c = UARTCharGet(UART5_BASE);
           UARTCharPutNonBlocking(UART5_BASE, c);
       }
}

void Bluetooth_Init(void)
{
    IntMasterEnable();

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOE); // Port used by UART5
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART5); // UART5 module

    GPIOPinConfigure(GPIO_PE4_U5RX);
    GPIOPinConfigure(GPIO_PE5_U5TX);
    GPIOPinTypeUART(GPIO_PORTE_BASE, GPIO_PIN_4 | GPIO_PIN_5);
    UARTConfigSetExpClk(UART5_BASE, SysCtlClockGet(), UART_BAUDRATE, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    IntEnable(INT_UART5);
    UARTIntEnable(UART5_BASE, UART_INT_RX | UART_INT_RT);
    UARTEnable(UART5_BASE);

//    UARTStdioConfig(0, UART_BAUDRATE, 16000000);

    UARTprintf("Bluetooth configured!\r\n");
}

void Bluetooth_ProcessInput()
{
    LED_Toggle(RED_LED);
}




