/*
 * led.c
 *
 *  Created on: Oct 4, 2022
 *      Author: Rodrigo Mascarenhas
 */

#include "led.h"

uint8_t RED_LED_STATE   = 0x0;
uint8_t BLUE_LED_STATE  = 0x0;
uint8_t GREEN_LED_STATE = 0x0;

void LED_Init(void)
{
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOF); // Port used by LEDs

    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_1);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_2);
    GPIOPinTypeGPIOOutput(GPIO_PORTF_BASE, GPIO_PIN_3);
}

void LED_Toggle(uint8_t LED)
{
    uint8_t LED_PIN    = 0x0;
    uint8_t *LED_STATE = &RED_LED_STATE;

    if (LED == RED_LED)   { LED_PIN = GPIO_PIN_1; LED_STATE = &RED_LED_STATE;   }
    if (LED == GREEN_LED) { LED_PIN = GPIO_PIN_3; LED_STATE = &GREEN_LED_STATE; }
    if (LED == BLUE_LED)  { LED_PIN = GPIO_PIN_2; LED_STATE = &BLUE_LED_STATE;  }

    bool is_led_on = *(LED_STATE) > 0x0;

    GPIOPinWrite(GPIO_PORTF_BASE, LED_PIN, (is_led_on ? 0x0 : LED_PIN));
    *LED_STATE = is_led_on ? 0x0: LED_PIN;
}

void Led_ToggleRed(void)   { LED_Toggle(RED_LED);   }
void LED_ToggleGreen(void) { LED_Toggle(GREEN_LED); }
void LED_ToggleBlue(void)  { LED_Toggle(BLUE_LED);  }
