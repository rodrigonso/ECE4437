/*
 * control.h
 *
 *  Created on: Nov 4, 2022
 *      Author: Rodrigo Mascarenhas
 */

#ifndef CONTROLLERS_CONTROL_H_
#define CONTROLLERS_CONTROL_H_

#include "drivers/motor.h"
#include "drivers/led.h"

enum STATES
{
    SYSTEM_STOP,
    SYSTEM_START,
    SYSTEM_TEST
};


void Control_Init(void);
void Control_Start(void);
void Control_Stop(void);
void Control_Test(void);
int Control_GetState(void);

#endif /* CONTROLLERS_CONTROL_H_ */
