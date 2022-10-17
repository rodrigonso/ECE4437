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

    // System Peripheral/GPIO Config
    SysCtlPeripheralEnable(SYSCTL_PERIPH_GPIOD);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC0);
    SysCtlPeripheralEnable(SYSCTL_PERIPH_ADC1);
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_0);
    GPIOPinTypeADC(GPIO_PORTD_BASE, GPIO_PIN_1);

    // Front sensor
    ADCSequenceConfigure(ADC0_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC0_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH6);
    ADCSequenceEnable(ADC0_BASE, 3);
    ADCIntEnable(ADC0_BASE, 3);

    // Right sensor
    ADCSequenceConfigure(ADC1_BASE, 3, ADC_TRIGGER_PROCESSOR, 0);
    ADCSequenceStepConfigure(ADC1_BASE, 3, 0, ADC_CTL_IE | ADC_CTL_END | ADC_CTL_CH7);
    ADCSequenceEnable(ADC1_BASE, 3);
    ADCIntEnable(ADC1_BASE, 3);

    UARTprintf("Distance sensor configured!\r\n");
}

uint32_t Distance_GetDistanceFront(void)
{
    uint32_t curr_distance = 0;
    ADCProcessorTrigger(ADC0_BASE, 3);
    while (!ADCIntStatus(ADC0_BASE, 3, false)) {}
    ADCIntClear(ADC0_BASE, 3);
    ADCSequenceDataGet(ADC0_BASE, 3, &curr_distance);
    return curr_distance;
}

uint32_t Distance_GetDistanceRight(void)
{
    uint32_t curr_distance = 0;
    ADCProcessorTrigger(ADC1_BASE, 3);
    while(!ADCIntStatus(ADC1_BASE, 3, false)) {}
    ADCIntClear(ADC1_BASE, 3);
    ADCSequenceDataGet(ADC1_BASE, 3, &curr_distance);
    return curr_distance;
}

void Distance_Print(void)
{
//    uint32_t test = Distance_GetDistanceFront();
//    float distance_f = 4544.5 * pow((float)test, -0.834);
//    float distance_r = 4544.5 * pow((float)Distance_GetDistanceRight(),-0.834);

    UARTprintf("Distance front: %d\r\n", Distance_GetDistanceFront());
    UARTprintf("Distance right: %d\r\n", Distance_GetDistanceRight());
}



#endif /* DRIVERS_DISTANCE_C_ */
