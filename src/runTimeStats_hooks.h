
#include <Arduino.h>
#include "FreeRTOS.h"

#ifndef RUN_TIME_STATS_HOOKS_H
#define RUN_TIME_STATS_HOOKS_H

#ifdef __cplusplus
extern "C" 
{
#endif

	//**************************************************
	// function prototypes
	//**************************************************

	void vMainConfigureTimerForRunTimeStats( void );
	unsigned long ulMainGetRunTimeCounterValue( void );

#ifdef __cplusplus
}
#endif

#endif // end RUN_TIME_STATS_HOOKS_H
