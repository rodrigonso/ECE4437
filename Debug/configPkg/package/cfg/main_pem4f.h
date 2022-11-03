/*
 *  Do not modify this file; it is automatically 
 *  generated and any modifications will be overwritten.
 *
 * @(#) xdc-B06
 */

#include <xdc/std.h>

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle TIMER_HWI_0;

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle CONSOLE_HWI_0;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle CONSOLE_SEMA_0;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle COMMAND_TASK_0;

#include <ti/sysbios/hal/Hwi.h>
extern const ti_sysbios_hal_Hwi_Handle BLUETOOTH_HWI_0;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle BLUETOOTH_SEMA_0;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle BLUETOOTH_TASK_0;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle PID_TASK_0;

#include <ti/sysbios/knl/Semaphore.h>
extern const ti_sysbios_knl_Semaphore_Handle PID_SEMA_0;

#include <ti/sysbios/knl/Task.h>
extern const ti_sysbios_knl_Task_Handle LED_TASK_0;

extern int xdc_runtime_Startup__EXECFXN__C;

extern int xdc_runtime_Startup__RESETFXN__C;

