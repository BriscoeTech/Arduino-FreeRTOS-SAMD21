FreeRTOS V8.2.3 for Arduino Samd21 Boards

This library will allow you to create FreeRtos Projects in the arduino IDE and run them on your Samd21 boards.



***************************************************************************************************************
Tested Boards:
 Sparkfun Samd21 Mini
 Sparkfun Samd21 Dev
 Adafruit Feather M0
 Atmel Xplained Samd21

 

***************************************************************************************************************
Nice To Have:
 
The rtos is currently using heap_3 and works fine, however you cannot measure how much heap is free.

If you figure out how to use heap_2, let me know! That will be a better implementation in that you can use
the function call xPortGetFreeHeapSize() in the task monitor for greater insight into whats going on under
the hood.

 



	
