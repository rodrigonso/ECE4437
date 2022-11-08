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
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);

    Bluetooth_Send("Light sensor initialized!\r\n");
}


int count = 0;
int state = 0;
bool isBlack;

// Read the value for the light sensor - This is a clock function
void LightSensor_Read(UArg arg0, UArg arg1) {
    while (1)
    {

        switch (state) {
        case 0:
            // set up light sensor
            GPIOPinTypeGPIOOutput(GPIO_PORTD_BASE, GPIO_PIN_3);         // Make PortD pin 3 output to charge the sensor
            GPIOPinWrite(GPIO_PORTD_BASE, GPIO_PIN_3, GPIO_PIN_3);      // Start charing the sensor
            if (count < 2) {                                            //threshold to start counting up
                count++;
            } else {
                state = 1;                                              //jump to case 1
                count = 0;                                              //reset counter
            }
            break;
        case 1:
            GPIOPinTypeGPIOInput(GPIO_PORTD_BASE, GPIO_PIN_3);          // Make PortD pin 3 input to time the decaying
            pinValue = GPIOPinRead(GPIO_PORTD_BASE, GPIO_PIN_3);        // Assign the value when sensor is in fully charged state
            if (pinValue & GPIO_PIN_3) {
                count++;                                                //start counting
            } else {
                state = 2;                                              //jump to case 2
            }
            break;
        case 2:
            if (count > 2) {                                            //threshold to determine when on black surface
                isBlack = true;                                         //on black surface

            } else {
                isBlack = false;                                        //if less than threshold assume on white surface
            }
            count = 0;                                                  //reset the counter
            state = 3;                                                  //jump to case 3
            break;
        case 3:
            if (count < 20) {
                count++;                                                //continue counting up if threshold is less than 20
            } else {
                count = 0;                                              //if greater than 20 reset the counter
                state = 0;
            }
            break;
        }
        LightSensor_CheckLine();                                                   //call function to determine the thickness of the line
        Task_yield();
    }
}

int lineCount = 0;
bool onBlack = false;
//function to determine thickness of the black tape
void LightSensor_CheckLine() {
    if (onBlack == false && isBlack == true) {                      //if previous state was white and current state is black
        onBlack = true;                                             //set previous state to black
        GPIOPinWrite(GPIO_PORTF_BASE, GPIO_PIN_1|GPIO_PIN_2, 0);
        lineCount = 1;                                              //start counting
    }

    if (onBlack == true && isBlack == true) {                       //if previous state was black and current state is also black
        lineCount++;                                                //keep counting
        if (lineCount > 20000) {
            lineCount = 20000;
        }
    }

    if (onBlack == true && isBlack == false) {                      //if previous state was black and current state is white
        onBlack = false;                                            //set previous state to white
        if (lineCount > 240) {                                      //if lineCount exceeds threshold for a single black line
            Control_Stop();                                             //stop the robot

        } else if (lineCount > 90) {                                //if encounter thin black line send data

        }
    }
}

