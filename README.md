# ECE 4437 - Maze Robot

## Intro
This robot is built on the Tiva-C platform and it is a project from the ECE 4437 - Embedded Microprocessor Systems course at the University of Houston. The goal of this project is to create a robot that can navigate a maze using the TI-RTOS real time operating system.

## Requirements

1. Robot must be able to make right turns and U-turns when a dead end is reached using a PID controller
2. Robot must communicate with user PC via bluetooth by using UART -- accept commands and also send data.
3. Robot must send back PID error data via bluetooth to PC
4. Robot must be able to detect thin black lines, and thick black lines (finish line)
5. Must use a TI-RTOS implementation for the robot's operation

## Hardware
As previously mentioned, this robot is built on the TI Tiva-C (EK-TM4C123GXL) platform. To meet the above requirements, the robot uses two analog distance sensors that is used for the PID controller, and one digital reflectance sensor which allows the robot to detect the thin/thick black lines on the ground.

## Software
This project was implemented in C using the TivaWare software package to interface with the Tiva-C microcontroller. As part of the requirement, the software for this robot is running with the TI-RTOS by the means of HWI, Tasks, and Semaphores.

Most tasks are periodic, which means a timer module of the Tiva-C is setup to count down and until the HWI for their respective timer is triggered. Inside the Timer ISR, the semaphore for that specific task is posted which allows the task to be run by the TI-RTOS scheduler.

![test](https://user-images.githubusercontent.com/46465969/204386864-cd091bbf-2eca-4e99-b802-8aa335e1bbb3.jpg)

## Demo
https://www.youtube.com/shorts/mt5m7SPoH5Q
