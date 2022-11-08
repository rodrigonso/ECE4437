/*
 * bluetooth.c
 *
 *  Created on: Sep 26, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "bluetooth.h"

int  BT_FIFO_IDX = 0;
int  BT_FIFO_CURRENT_IDX = 0;
char BT_FIFO_BUFFER[10];

Command bluetooth_command_table[] =
{

 { "START",  &Control_Start  },
 { "STOP",   &Control_Stop   },

};

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

    UARTStdioConfig(0, UART_BAUDRATE, SysCtlClockGet());

//    UARTprintf("Bluetooth configured!\r\n");
    Bluetooth_Send("Bluetooth initialized!\r\n");
}

void Bluetooth_IntHandler(void)
{
    uint32_t ui32Status;

    // Get the interrrupt status.
    ui32Status = UARTIntStatus(UART5_BASE, true);

    // Clear the asserted interrupts.
    UARTIntClear(UART5_BASE, ui32Status);

    while (UARTCharsAvail(UART5_BASE))
    {
        char c = UARTCharGetNonBlocking(UART5_BASE);
        UARTCharPutNonBlocking(UART5_BASE, c);

        if (BT_FIFO_CURRENT_IDX >= 10 || c == '\r')
        {
            BT_FIFO_IDX = BT_FIFO_CURRENT_IDX;
            BT_FIFO_CURRENT_IDX = 0;
            Semaphore_post(BLUETOOTH_SEMA_0);
            break;
        }

        if (c != '\b')
            BT_FIFO_BUFFER[BT_FIFO_CURRENT_IDX++] = c;
        else
        {
            BT_FIFO_BUFFER[--BT_FIFO_CURRENT_IDX] = (char) 0;
            UARTCharPutNonBlocking(UART5_BASE, (char) 0);
        }
    }
}

void Bluetooth_CommandHandler(UArg arg0, UArg arg1)
{

    while (1)
    {
        Semaphore_pend(BLUETOOTH_SEMA_0, BIOS_WAIT_FOREVER);

        Command *table_entry = &bluetooth_command_table[0];
        while (table_entry->name)
        {
            if (strncmp(table_entry->name, BT_FIFO_BUFFER, BT_FIFO_IDX) == 0)
            {
                Bluetooth_Send("Command received: ");
                Bluetooth_Send(table_entry->name);
                Bluetooth_Send("\r\n");
                table_entry->fun_ptr();
                break;
            }
            table_entry++;
        }

        Bluetooth_EraseBuffer();
        Task_yield();
    }
}

void Bluetooth_Send(char str[])
{

    int i = 0;
    // Loop while there are more characters to send.
    while(i <= strlen(str))
    {
        // Write the next character to the UART.
        UARTCharPut(UART5_BASE, str[i++]);
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

void Bluetooth_EraseBuffer(void)
{
    int i;
    for (i = 0; i <= BT_FIFO_IDX; i++)
        BT_FIFO_BUFFER[i] = (char)0;

    BT_FIFO_IDX = 0;
}



