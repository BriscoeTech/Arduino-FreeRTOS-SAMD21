
#include <Arduino.h>
#include "FreeRTOS.h"
#include "task.h"

#ifndef ERROR_HOOKS_H
#define ERROR_HOOKS_H

	#ifdef __cplusplus

		//**************************************************
		// Cpp function prototypes
		//**************************************************

		// set the error serial port for debugging asserts and crashes
		void vSetErrorSerial(Stream *serial);

	extern "C"
	{
	#endif

		//**************************************************
		// defines
		//**************************************************


		//**************************************************
		// C function prototypes
		//**************************************************

		// set the error led to use by the rtos
		void vSetErrorLed(uint8_t pin, uint8_t activeState);

		// remove a linux or windows path from a file path
		// will leave file name remaining
		const char* removePath(const char* path);

		// called on fatal error (interrupts disabled already)
		void rtosFatalError(void);

		// fatal error print out what file assert failed
		void rtosFatalErrorSerialPrint(unsigned long ulLine, const char *pcFileName, uint8_t valueA, const char* evaluation, uint8_t valueB);

		// called on full heap or malloc failure
		void vApplicationMallocFailedHook(void);

		// called on full stack
		void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName );



		// blink an error code out the default led when the rtos has crashed
		void errorBlink(int errorNumber);

		// will delay the processors using nops
		// this is used when the rtos has crashed and we cannot use more advanced timing
		void vNopDelayMS(unsigned long millis);

	#ifdef __cplusplus
	}
	#endif

#endif
