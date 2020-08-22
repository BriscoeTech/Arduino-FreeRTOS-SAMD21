/* This has been copied then modified from
 * FreeRTOS/Demo/CORTEX_M0+_Atmel_SAMD20_XPlained/RTOSDemo/src/config/FreeRTOSConfig.h
 */
/*
 * FreeRTOS Kernel V10.2.1
 * Copyright (C) 2019 Amazon.com, Inc. or its affiliates.  All Rights Reserved.
 *
 * Permission is hereby granted, free of charge, to any person obtaining a copy of
 * this software and associated documentation files (the "Software"), to deal in
 * the Software without restriction, including without limitation the rights to
 * use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of
 * the Software, and to permit persons to whom the Software is furnished to do so,
 * subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all
 * copies or substantial portions of the Software.
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS
 * FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR
 * COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER
 * IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN
 * CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 *
 * http://www.FreeRTOS.org
 * http://aws.amazon.com/freertos
 *
 * 1 tab == 4 spaces!
 */


#ifndef FREERTOS_CONFIG_H
#define FREERTOS_CONFIG_H

/*-----------------------------------------------------------
 * Application specific definitions.
 *
 * These definitions should be adjusted for your particular hardware and
 * application requirements.
 *
 * THESE PARAMETERS ARE DESCRIBED WITHIN THE 'CONFIGURATION' SECTION OF THE
 * FreeRTOS API DOCUMENTATION AVAILABLE ON THE FreeRTOS.org WEB SITE.
 *
 * See http://www.freertos.org/a00110.html
 *----------------------------------------------------------*/


#define configUSE_PREEMPTION			1
#define configUSE_IDLE_HOOK				1
#define configUSE_TICK_HOOK				0
#define configCPU_CLOCK_HZ				( ( unsigned long ) F_CPU  )
#define configTICK_RATE_HZ				( ( TickType_t ) 1000 )
#define configMAX_PRIORITIES			( 9 )
#define configMINIMAL_STACK_SIZE		( ( unsigned short ) 150 )
#define configTOTAL_HEAP_SIZE			( ( size_t ) ( 14 * 1024 ) )
#define configMAX_TASK_NAME_LEN			( 16 ) //includes string null terminator
#define configUSE_TRACE_FACILITY		1
#define configUSE_16_BIT_TICKS			0
#define configIDLE_SHOULD_YIELD			1
#define configUSE_MUTEXES				1
#define configQUEUE_REGISTRY_SIZE		8
#define configCHECK_FOR_STACK_OVERFLOW	2
#define configUSE_RECURSIVE_MUTEXES		1
#define configUSE_MALLOC_FAILED_HOOK	1
#define configUSE_APPLICATION_TASK_TAG	0
#define configUSE_COUNTING_SEMAPHORES	1
#define configUSE_QUEUE_SETS			1
#define configSUPPORT_STATIC_ALLOCATION 0
#define configSUPPORT_DYNAMIC_ALLOCATION 1

/* Run time stats related definitions. */
#define configGENERATE_RUN_TIME_STATS	1

/* Arduino framework integration */
#define portCONFIGURE_TIMER_FOR_RUN_TIME_STATS() 	vMainConfigureTimerForRunTimeStats() // see runTimeStats_hooks.h
#define portGET_RUN_TIME_COUNTER_VALUE() 			ulMainGetRunTimeCounterValue() // see runTimeStats_hooks.h

/* This demo makes use of one or more example stats formatting functions.  These
format the raw data provided by the uxTaskGetSystemState() function in to human
readable ASCII form.  See the notes in the implementation of vTaskList() within
FreeRTOS/Source/tasks.c for limitations. */
#define configUSE_STATS_FORMATTING_FUNCTIONS	1

#define configUSE_MUTEXES        				1
#define INCLUDE_uxTaskGetStackHighWaterMark 	1
#define INCLUDE_xTaskGetIdleTaskHandle 			1
#define configUSE_MALLOC_FAILED_HOOK			1

/* Co-routine definitions. */
#define configUSE_CO_ROUTINES 		     0
#define configMAX_CO_ROUTINE_PRIORITIES ( 2 )

/* Software timer definitions. */
#define configUSE_TIMERS				1
#define configTIMER_TASK_PRIORITY		( 2 )
#define configTIMER_QUEUE_LENGTH		10
#define configTIMER_TASK_STACK_DEPTH	( configMINIMAL_STACK_SIZE )

/* Set the following definitions to 1 to include the API function, or zero
to exclude the API function. */
#define INCLUDE_xTaskGetCurrentTaskHandle   1
#define INCLUDE_vTaskPrioritySet			1
#define INCLUDE_uxTaskPriorityGet			1
#define INCLUDE_vTaskDelete					1
#define INCLUDE_vTaskCleanUpResources		1
#define INCLUDE_vTaskSuspend				1
#define INCLUDE_vTaskDelayUntil				1
#define INCLUDE_vTaskDelay					1
#define INCLUDE_eTaskGetState				1

/* Arduino framework integration */
// calibration factor for vNopDelayMS in error_hooks.c
// used to set accuracy of nopDelayMS function
// this was experimentally chosen from a samd21 processor at 32khz
#define configCAL_FACTOR (F_CPU/6000)

/* Arduino framework integration */
#if 0
	// disable interrupts and blink error code
	extern void rtosFatalError(void); // see error_hooks.h
	#define configASSERT( x ) \
		if( ( x ) == 0 ) { rtosFatalError(); }
#else
	// print a error file and line number out user specified serial port
	// disable interrupts and blink error code
	extern void rtosFatalErrorSerial(unsigned long ulLine, const char * const pcFileName); // see error_hooks.h
	extern const char* removePath(const char* path); // see error_hooks.h
	#define configASSERT( x ) \
		if( ( x ) == 0 ) { rtosFatalErrorSerial( __LINE__, removePath(__FILE__) ); }

	// assert you can use to also print the value that caused the failure
	// Useful for debugging, but not FreeRtos standard
	#define configPrintASSERT( x, v1, s, v2 ) \
		if( ( x ) == 0 ) { rtosFatalErrorSerialPrint( __LINE__, removePath(__FILE__), v1, s, v2 ); }
#endif

/* Arduino framework integration */
// article to help wade through and figure out proper interrupt settings:
// https://community.arm.com/developer/ip-products/system/b/embedded-blog/posts/cutting-through-the-confusion-with-arm-cortex-m-interrupt-priorities

/* Cortex-M specific definitions. */
#define configPRIO_BITS		3 // SAMD21 has only 4 priority levels. pg32 of datasheet.

/* The lowest interrupt priority that can be used in a call to a "set priority"
function. */
#define configLIBRARY_LOWEST_INTERRUPT_PRIORITY			 0x03 // lowest priority

/* The highest interrupt priority that can be used by any interrupt service
routine that makes calls to interrupt safe FreeRTOS API functions.  DO NOT CALL
INTERRUPT SAFE FREERTOS API FUNCTIONS FROM ANY INTERRUPT THAT HAS A HIGHER
PRIORITY THAN THIS! (higher priorities are lower numeric values. */
// See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html.
#define configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY	0x01 // highest priority

/* Interrupt priorities used by the kernel port layer itself.  These are generic
to all Cortex-M ports, and do not rely on any particular library functions. */
#define configKERNEL_INTERRUPT_PRIORITY 		( configLIBRARY_LOWEST_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )
/* !!!! configMAX_SYSCALL_INTERRUPT_PRIORITY must not be set to zero !!!!
See http://www.FreeRTOS.org/RTOS-Cortex-M3-M4.html. */
#define configMAX_SYSCALL_INTERRUPT_PRIORITY 	( configLIBRARY_MAX_SYSCALL_INTERRUPT_PRIORITY << (8 - configPRIO_BITS) )

/* Definitions that map the FreeRTOS port interrupt handlers to their CMSIS
standard names. */
#define vPortSVCHandler SVC_Handler
#define xPortPendSVHandler PendSV_Handler
//#define xPortSysTickHandler SysTick_Handler

/* The size of the global output buffer that is available for use when there
are multiple command interpreters running at once (for example, one on a UART
and one on TCP/IP).  This is done to prevent an output buffer being defined by
each implementation - which would waste RAM.  In this case, there is only one
command interpreter running. */
#define configCOMMAND_INT_MAX_OUTPUT_SIZE 2048

#endif /* FREERTOS_CONFIG_H */

