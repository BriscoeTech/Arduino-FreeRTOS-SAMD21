###  FreeRTOS V8.2.3 for Arduino Samd21 Boards  

####  This library will allow you to create FreeRtos Projects in the arduino IDE and run them on your Samd21 boards.  


***************************************************************************************************************
Tested Boards:  
 Sparkfun Samd21 Mini  
 Sparkfun Samd21 Dev  
 Adafruit Feather M0  
 Atmel Xplained Samd21  
 
***************************************************************************************************************

#### How to wrap malloc/free/realloc/calloc system functions
If you want wrap the `malloc`, `free`, `realloc` and `calloc` system functions with those provided by FreeRTOS, simply use the *--wrap* option passed to the gcc linker, by appending the following line to the `compiler.ldflags=` line of the [**platform.txt**](https://github.com/arduino/ArduinoCore-samd/blob/master/platform.txt) file:

```
-Wl,--wrap=malloc -Wl,--wrap=free -Wl,--wrap=calloc -Wl,--wrap=realloc
```

 
 
