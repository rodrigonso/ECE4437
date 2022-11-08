/*
 * config.h
 *
 *  Created on: Oct 4, 2022
 *      Author: Rodrigo Mascarenhas
 */

#ifndef CONFIG_H_
#define CONFIG_H_

#include <stdint.h>
#include <stdbool.h>
#include <stdio.h>
#include <ti/sysbios/knl/Task.h>

#define UART_BAUDRATE 115200
#define TASKSTACKSIZE   512

typedef struct
{
    char name[10];
    void (*fun_ptr)(void);
} Command;

// Initialization
//Task_Handle read_front;
//Task_Params read_front_params;
//Char readFrontStack[TASKSTACKSIZE];
//
//Task_Handle read_right;
//Task_Params read_right_params;
//Char readRightStack[TASKSTACKSIZE];

// Instantiation
//Task_Params_init(&read_front_params);
//read_front_params.stackSize = TASKSTACKSIZE;
//read_front_params.priority = 3;
//read_front_params.stack = &readFrontStack;
//read_front = Task_create((Task_FuncPtr)Distance_GetFront, &read_front_params, 0);
//
//Task_Params_init(&distance_read_right_params);
//read_right_params.stackSize = TASKSTACKSIZE;
//read_right_params.priority = 3;
//read_right_params.stack = &readRightStack;
//read_right = Task_create((Task_FuncPtr)Distance_GetRight, &read_right_params, 0);

#endif /* CONFIG_H_ */
