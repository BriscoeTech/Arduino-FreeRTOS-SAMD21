FreeRTOS V8.2.3 for Arduino Samd21 Boards

This library will allow you to create FreeRtos Projects in the arduino IDE and run them on your Samd21 boards.







***************************************************************************************************************
Tested Boards:
 Sparkfun Samd21 Mini
 Sparkfun Samd21 Dev
 Adafruit Feather M0
 Atmel Xplained Samd21

 
 
 
 
 
 
 
 
 
 ***************************************************************************************************************
 Known Issue:
 
 Millis() and Micros() are incorrect, they are off by a factor of 10. For correct timing, you need to divide the
 the values returned from these functions by 10.
 
 Why? The RTOS is using the same hardware timer as these functions, and I have not figured out yet how to either
	1) Scale down the clock initialized by the rtos
	2) Have the rtos use a different timer for the rtos tick that's not shared with any arduino functions
	2) overload the original functions with new functions that automatically scale it down by 10

If you figure out how to do this, let me know!

***************************************************************************************************************
Nice To Have:
 
The rtos is currently using heap_3 and works fine, however you cannot measure how much heap is free.

If you figure out how to use heap_2, let me know! That will be a better implementation in that you can use
the function call xPortGetFreeHeapSize() in the task monitor for greater insight into whats going on under
the hood.

 



	
