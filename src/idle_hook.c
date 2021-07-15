
#include <FreeRTOS.h>
#include <Arduino.h>
//Arduino loop as task
#include "task.h"

uint8_t loopAsTask = 0;
TaskHandle_t loopHandle;

// this is referring to the loop function of your arduino project
extern void loop(void); 

void  __attribute__((weak)) vApplicationIdleHook( void ) 
{
    if (!loopAsTask)
    {
        loop(); //will use your projects loop function as the rtos idle loop
    }
}

void loopTask(void *pvParameters)
{
    while(1)
    {
        loop();
    }
}

void runLoopAsTask(uint16_t stack, uint16_t priority)
{
    loopAsTask = 1;
    xTaskCreate(loopTask, "loop", stack, ( void * ) NULL, ( (UBaseType_t)priority | portPRIVILEGE_BIT ) , &loopHandle);
}
