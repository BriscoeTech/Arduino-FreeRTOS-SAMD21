
// External Libraries
#include <FreeRTOS_SAMD21.h> //samd21

#include "GameMessage.h"
#include "GameData.h"
#include "GameThing.c"


// This example project tests that a .ino, c header, or cpp header can include and compile the library
// Keeping this example around to make sure that any library architecture changes will still compile in a arduino project
// Found a obscure compiling error that would occur if the librarys header file did not include the arduino library explicitly
// Also useful to make sure rtos C code is not trying to include Cpp arduino functions


//**************************************************************************
void setup() 
{

}


//**************************************************************************
void loop() 
{

}

