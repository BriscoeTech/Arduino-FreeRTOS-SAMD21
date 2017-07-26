

#include <Arduino.h>
#include "FreeRTOS.h"
#include "task.h"


#ifndef ERROR_HOOKS_H
#define ERROR_HOOKS_H

	//**************************************************
	// defines
	//**************************************************

	// calibration factor for delayMS
	// this was experimentally chosen from a samd21 processor at 32khz
	// used to set accuracy of nopDelayMS function
	#define CAL_FACTOR (F_CPU/6000)
	
	//**************************************************
	// function prototypes
	//**************************************************

	// called on fatal error (interrupts disabled already)
	void rtosFatalError(void);

	// called on empty heap space
	void vApplicationMallocFailedHook(void);

	// called on empty stack
	void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName );
	
	
	// set the error led to use by the rtos
	void vSetErrorLed(uint8_t pin, uint8_t activeState);
	
	// blink an error code out the default led when the rtos has crashed
	void errorBlink(int errorNumber);
	
	// will delay the processors using nops
	// this is used when the rtos has crashed and we cannot use more advanced timing
	void nopDelayMS(unsigned long millis);
	

#endif