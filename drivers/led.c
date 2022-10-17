/*
 * led.c
 *
 *  Created on: Oct 4, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "led.h"

uint8_t LED_STATE   = 0x0;

void LED_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Port used by LEDs

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
}

void LED_Toggle(uint32_t arg0)
{
    uint8_t LED_PIN    = 0x0;

    if (arg0 == RED_LED)   { LED_PIN = GPIO_PIN_1; }
    if (arg0 == GREEN_LED) { LED_PIN = GPIO_PIN_3; }
    if (arg0 == BLUE_LED)  { LED_PIN = GPIO_PIN_2; }

    LED_STATE ^= LED_PIN;
    GPIOPinWrite(GPIO_PORTF_BASE, LED_PIN, LED_STATE);
}

void Led_ToggleRed(void)   { LED_Toggle(RED_LED);   }
void LED_ToggleGreen(void) { LED_Toggle(GREEN_LED); }
void LED_ToggleBlue(void)  { LED_Toggle(BLUE_LED);  }
