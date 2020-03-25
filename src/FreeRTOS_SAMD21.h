

#ifndef FREE_RTOS_SAMD21_H
#define FREE_RTOS_SAMD21_H

	#include <Arduino.h> //required to prevent a compiling error when a cpp header file tries to include this library

	// Rtos core library
	#include <FreeRTOS.h>
	#include <timers.h>
	#include <task.h>
	#include <stack_macros.h>
	#include <semphr.h>
	#include <queue.h>
	#include <projdefs.h>
	#include <mpu_wrappers.h>
	#include <list.h>
	#include <FreeRTOSConfig.h>
	#include <event_groups.h>
	#include <deprecated_definitions.h>
	#include <croutine.h>
	#include <message_buffer.h>
	#include <stream_buffer.h>

	// hardware specific port files
	#include <portmacro.h>
	#include <portable.h>
	
	// added helper filed for Arduino support
	#include <error_hooks.h>
	#include <runTimeStats_hooks.h>


#endif
