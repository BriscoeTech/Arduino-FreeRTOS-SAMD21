
#include "error_hooks.h"
#include "FreeRTOSConfig.h" //for configCAL_FACTOR

//************************************************************************
// global variables

int ErrorLed_Pin     	  =  13; //default arduino led pin
int ErrorLed_ActiveState  =  LOW;

//************************************************************************

// called on fatal error (interrupts disabled already)
void rtosFatalError(void) 
{

  //Serial.println("Fatal Error");
  
  while (1)
  {
    errorBlink(3);
  }
}

// called on full heap or malloc failure
void vApplicationMallocFailedHook(void) 
{

  //Serial.println("Malloc Failed");
  
  while (1)
  {
    errorBlink(1);
  }
}

// called on full stack
void vApplicationStackOverflowHook( TaskHandle_t xTask, char *pcTaskName )
{

  //Serial.print("Stack Overflow: ");
  //Serial.println(pcTaskName);
  
  while (1)
  {
    errorBlink(2);
  }
}

//************************************************************************

// set the error led to use by the rtos
void vSetErrorLed(uint8_t pin, uint8_t activeState)
{
	ErrorLed_Pin = pin;
	ErrorLed_ActiveState = activeState;
}

// blink an error code out the default led when the rtos has crashed
void errorBlink(int errorNumber)
{
  pinMode(ErrorLed_Pin, OUTPUT); 
  
  for(int x=0; x<errorNumber; ++x)
  {
    digitalWrite(ErrorLed_Pin,  ErrorLed_ActiveState);   
    vNopDelayMS(100);
    digitalWrite(ErrorLed_Pin, !ErrorLed_ActiveState);
    vNopDelayMS(100);   
  }

  vNopDelayMS(1000);
}

// will delay the processors using nops
// this is used when the rtos has crashed and we cannot use more advanced timing
// assert will cause interrupts to be disabled and delay() to fail, but this will work
// note this function does not play nice with interrupts apparently, this does not replace delay() which is more interrupt friendly
void vNopDelayMS(unsigned long millis) 
{
  unsigned long iterations = millis * configCAL_FACTOR;
  unsigned long i;
  for(i = 0; i < iterations; ++i) 
  {
    asm volatile("nop\n\t");
  }
}

//************************************************************************
