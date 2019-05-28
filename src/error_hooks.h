

#include <Arduino.h>
#include "FreeRTOS.h"
#include "task.h"


#ifndef ERROR_HOOKS_H
#define ERROR_HOOKS_H

	//**************************************************
	// defines
	//**************************************************

	// calibration factor for vNopDelayMS
	// used to set accuracy of nopDelayMS function
	#if defined (__SAMD21G18A__)
		// this was experimentally chosen from a samd21 processor at 32khz
		#define CAL_FACTOR (F_CPU/6000)
	#elif defined (__SAMD51__)
		// assuming same architecture noop delay as samd21 for now, need to test
		#define CAL_FACTOR (F_CPU/6000)
	#else
		#error Processor architecture not recognized in FreeRtos error_hooks.h, may need to define CAL_FACTOR for this processor.
	#endif
	
	//**************************************************
	// function prototypes
	//**************************************************

	// called on fatal error (interrupts disabled already)
	void rtosFatalError(void);

	// called on full heap or malloc failure
	void vApplicationMallocFailedHook(void);

	// called on full stack
	void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName );
	
	
	// set the error led to use by the rtos
	void vSetErrorLed(uint8_t pin, uint8_t activeState);
	
	// blink an error code out the default led when the rtos has crashed
	void errorBlink(int errorNumber);
	
	// will delay the processors using nops
	// this is used when the rtos has crashed and we cannot use more advanced timing
	void vNopDelayMS(unsigned long millis);
	

#endif