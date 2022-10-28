/*
 * distance.c
 *
 *  Created on: Oct 7, 2022
 *      Author: Rodrigo Mascarenhas
 */

#ifndef DRIVERS_DISTANCE_C_
#define DRIVERS_DISTANCE_C_

#include "distance.h"

void Distance_Init(void)
{
    distance_front = 0;
    distance_right = 0;

    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);

    SysCtlDelay(6);

    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceConfigure(ADC1_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);

    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH6);
    ADCSequenceStepConfigure(ADC1_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH7);

    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);

    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0);
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_1);

    ADCSequenceEnable(ADC0_BASE, 3);
    ADCSequenceEnable(ADC1_BASE, 3);

    Bluetooth_Send("Distance initialized!\r\n");
}

uint32_t Distance_GetDistanceFront(void)
{
    ADCProcessorTrigger(ADC0_BASE, 3);
    ADCIntClear(ADC0_BASE, 3);
    ADCSequenceDataGet(ADC0_BASE, 3, &distance_front);
    return distance_front;
}

uint32_t Distance_GetDistanceRight(void)
{
    ADCProcessorTrigger(ADC1_BASE, 3);
    ADCIntClear(ADC1_BASE, 3);
    ADCSequenceDataGet(ADC1_BASE, 3, &distance_right);
    return distance_right;
}

#endif /* DRIVERS_DISTANCE_C_ */
