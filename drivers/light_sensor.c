/*
 * light_sensor.c
 *
 *  Created on: Nov 6, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "light_sensor.h"

int sensor_state = IDLE;
int sensor_count = 0;
bool should_stop = false;
bool is_black = false;

void LightSensor_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

    Bluetooth_Send("Light sensor initialized!\r\n");
}


void LightSensor_Read(UArg arg0, UArg arg1)
{
    while (1)
    {
        Semaphore_pend(PID_SEMA_0, BIOS_WAIT_FOREVER);

        uint32_t sensor_val;
        switch (sensor_state)
        {
            case IDLE:
                GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3);
                GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);

                if (sensor_count < 2)
                    sensor_count++;
                else
                {
                    sensor_state = READY;
                    sensor_count = 0;
                }
                break;

            case READY:
                GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_3);
                sensor_val = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3);

                if (sensor_val & GPIO_PIN_3)
                    sensor_count++;

                else
                    sensor_state = ONE_LINE;

                break;

            case ONE_LINE:
                if (sensor_count > 2)
                    is_black = true;
                else
                    is_black = false;

                sensor_count = 0;
                sensor_state = TWO_LINES;
                break;

            case TWO_LINES:
                if (sensor_count < 20)
                    sensor_count++;

                else {
                    sensor_count = 0;
                    sensor_state = IDLE;
                }

                break;
        }

        LightSensor_CheckLine();

        char *out = (char *)malloc(16*sizeof(char));
        sprintf(out, "Light sensor: %d\r\n", sensor_val);
        Bluetooth_Send(out);
        free(out);

        Task_yield();
    }
}

int line_count = 0;

void LightSensor_CheckLine(void)
{
    if (!should_stop && is_black)
    {
        should_stop = true;
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2, 0);
        line_count = 1;
    }

    if (should_stop && is_black)
    {
        line_count++;
        if (line_count > LINE_COUNT_MAX)
            line_count = LINE_COUNT_MAX;
    }

    if (should_stop && !is_black)
    {
        should_stop = false;
        if (line_count > LINE_COUNT_MIN)
        {

            // TODO: call stop
            Control_Stop();
        }
        else if (line_count > 90)
        {
            // TODO: send data
        }
    }
}

