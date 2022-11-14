/*
 * light_sensor.c
 *
 *  Created on: Nov 6, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "light_sensor.h"

void LightSensor_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    Bluetooth_Send("Light sensor initialized!\r\n");
}



// Read the value for the light sensor - This is a clock function
void LightSensor_Read(UArg arg0, UArg arg1) {
    while (1)
    {
        Semaphore_pend(LIGHT_SEMA_0, BIOS_WAIT_FOREVER);
        int count = 0;

        GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3);
        GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);

        SysCtlDelay(100);

        GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_3);
        while (GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3))
        {
            count++;
        }

        testPrint(count);
//        if (count > 20000) Control_Stop();
        Task_yield();
    }
}

void testPrint(int val)
{
    char * out = (char*)malloc(16*sizeof(char));
    sprintf(out, "COUNT: %d\r\n", val);
    Bluetooth_Send(out);
    free(out);
}


