/*
 * light_sensor.c
 *
 *  Created on: Nov 6, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "light_sensor.h"

int line_count = 0;
int running_time = 0;

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

        SysCtlDelay(15 * (SysCtlClockGet() / 3 / 1000000)); // 15 microseconds delay to allow sensor capacitor to charge

        GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_3);
        while (GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3))
        {
            count++;
        }

        if (count >= LIGHT_SENSOR_THRESHOLD)
        {
            line_count++;
        }
        else
        {
            if (LightSensor_CheckLine(count) == THIN_LINE)
            {
                Bluetooth_Send("Thin line\r\n");
//                if (Control_GetSendData() == true)
//                {
//                    LED_Disable(BLUE_LED);
//                    Control_SetSendData(false);
//                    Bluetooth_Send("Stop sending\r\n");
//                } else {
//                    LED_Enable(BLUE_LED);
//                    Control_SetSendData(true);
//                    Bluetooth_Send("Start sending\r\n");
//                }
            }
            line_count = 0;
        }

        if (LightSensor_CheckLine(count) == THICK_LINE)
        {
            Bluetooth_Send("Finish line...stopping!\r\n");
            Control_Stop();
            line_count = 0;
        }
        Task_yield();
    }
}


int LightSensor_CheckLine(int count)
{
    if (count >= 20) return THICK_LINE;
    else if (count > 5 && count < 20) return THIN_LINE;
    else return -1;
}
