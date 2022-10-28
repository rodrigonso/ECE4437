/*
 * console.c
 *
 *  Created on: Oct 8, 2022
 *      Author: Rodrigo Mascarenhas
 */


#include "console.h"

int  CNSL_FIFO_IDX = 0;
int  CNSL_FIFO_CURRENT_IDX = 0;
char CNSL_FIFO_BUFFER[10];

Command console_command_table[] =
{

 { "START",  Motor_Start  },
 { "STOP",   Motor_Stop   },

};

void Console_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_UART0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOA);

    GPIOPinConfigure(GPIO_PA0_U0RX);
    GPIOPinConfigure(GPIO_PA1_U0TX);
    GPIOPinTypeUART(GPIO_PORTA_BASE, GPIO_PIN_0 | GPIO_PIN_1);
    UARTConfigSetExpClk(UART0_BASE, SysCtlClockGet(), UART_BAUDRATE, (UART_CONFIG_WLEN_8 | UART_CONFIG_STOP_ONE | UART_CONFIG_PAR_NONE));

    IntEnable(INT_UART0);
    UARTIntEnable(UART0_BASE, UART_INT_RX | UART_INT_RT);
    UARTEnable(UART0_BASE);

    UARTFIFOEnable(UART0_BASE);

    UARTStdioConfig(0, UART_BAUDRATE, SysCtlClockGet());
    UARTprintf("Console configured!\r\n");
}

void Console_Send(const uint8_t *pui8Buffer, uint32_t ui32Count)
{
    // Loop while there are more characters to send.
    while(ui32Count--)
    {
        // Write the next character to the UART.
        UARTCharPutNonBlocking(UART0_BASE, *pui8Buffer++);
    }
}

void Console_Print(char str[])
{
    int i;
    for (i = 0; i < strlen(str); i++)
        UARTCharPut(UART0_BASE, str[i]);
}

void Console_IntHandler(void)
{
    uint32_t ui32Status;

    // Get the interrrupt status.
    ui32Status = UARTIntStatus(UART0_BASE, true);

    // Clear the asserted interrupts.
    UARTIntClear(UART0_BASE, ui32Status);

    while (UARTCharsAvail(UART0_BASE))
    {
        char c = UARTCharGetNonBlocking(UART0_BASE);
        UARTCharPutNonBlocking(UART0_BASE, c);

        if (CNSL_FIFO_CURRENT_IDX >= 10 || c == '\r')
        {
            CNSL_FIFO_IDX = CNSL_FIFO_CURRENT_IDX;
            CNSL_FIFO_CURRENT_IDX = 0;
            Semaphore_post(CONSOLE_SEMA_0);
            break;
        }
        CNSL_FIFO_BUFFER[CNSL_FIFO_CURRENT_IDX++] = c;
    }
}

void Console_HandleCommand(void)
{

    while (1)
    {
        Semaphore_pend(CONSOLE_SEMA_0, BIOS_WAIT_FOREVER);

        Command *table_entry = &console_command_table[0];
        while (table_entry->name)
        {
            if (strncmp(table_entry->name, CNSL_FIFO_BUFFER, CNSL_FIFO_IDX) == 0)
            {
                UARTprintf("Command received: ");
                UARTprintf(table_entry->name);
                UARTprintf("\r\n");
                table_entry->fun_ptr(0, 0);
                break;
            }
            table_entry++;
        }

        Task_yield();
    }
}





