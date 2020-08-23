//**************************************************************************
// FreeRtos on Samd21
// By Scott Briscoe
//
// Project is a simple test to make sure the different rtos failure detections
// are caught and the error led to blink properly.
//
// A great demo to also explore the common reasons the rtos crashes and how
// to avoid them
//
//**************************************************************************

#include <FreeRTOS_SAMD21.h>

//**************************************************************************
// Type Defines and Constants
//**************************************************************************

// change this to cause different errors to be compiled and run
#define ERROR_CHECKING	2	//0 for off, 1-6 to select failure mode to compile


#define  ERROR_LED_PIN  13 //Led Pin: Typical Arduino Board
//#define  ERROR_LED_PIN  2 //Led Pin: samd21 xplained board

#define ERROR_LED_LIGHTUP_STATE  HIGH // the state that makes the led light up on your board, either low or high

// Select the serial port the project should use and communicate over
// Some boards use SerialUSB, some use Serial
#define SERIAL          SerialUSB //Sparkfun Samd21 Boards
//#define SERIAL          Serial //Adafruit, other Samd21 Boards

//**************************************************************************
// global variables
//**************************************************************************
TaskHandle_t Handle_aTask;
TaskHandle_t Handle_bTask;
TaskHandle_t Handle_monitorTask;

//**************************************************************************
// Can use these function for RTOS delays
// Takes into account processor speed
// Use these instead of delay(...) in rtos tasks
//**************************************************************************
void myDelayUs(int us)
{
  vTaskDelay( us / portTICK_PERIOD_US );  
}

void myDelayMs(int ms)
{
  vTaskDelay( (ms * 1000) / portTICK_PERIOD_US );  
}

void myDelayMsUntil(TickType_t *previousWakeTime, int ms)
{
  vTaskDelayUntil( previousWakeTime, (ms * 1000) / portTICK_PERIOD_US );  
}


#if ERROR_CHECKING == 2
void endlessRecursion(int l)
{
	int a[l];
	long sum = 0;

	for(int x=0; x<l; ++x)
	{
		sum += a[x];
	}

	SERIAL.print("Level ");
	SERIAL.print(l);
	SERIAL.print(" ");
	SERIAL.println(sum);
	SERIAL.flush();
	
	myDelayMs(500);

	endlessRecursion(l + 1);
	return;
}
#endif



//*****************************************************************
// Create a thread that prints out A to the screen every two seconds
// this task will delete its self after printing out afew messages
//*****************************************************************
static void threadA( void *pvParameters ) 
{
  
	SERIAL.println("Thread A: Started");

	#if ERROR_CHECKING == 1
		while(1)
		{
			// cause a memory leak, grabbing from ram and not stacks or heap
			// also simulates how some libraries keep allocating more and more objects
			// this is not caught by the rtos by default, is not a rtos malloc failure
			// enabling the memory wrapping feature will cause library to catch this
			// is also a good test to see if you have wrapping the optional memory feature properly
			SERIAL.print("L");
			SERIAL.flush();

			char *memLeak = new char[300];
			sprintf(memLeak, "%d", random(0, 10));
			SERIAL.print(memLeak);
			SERIAL.flush();
			
			myDelayMs(500);
		}

	#elif ERROR_CHECKING == 2
		// cause a stack overflow
		// call a endless recursive function
		endlessRecursion(1);

	#elif ERROR_CHECKING == 3
		// generate a failed assert, this is testing the rtos asserts work
		// cause a rtosFatalError
		configASSERT( 0 );

	#else
		// normal run, print out A to terminal
		for(int x=0; x<100; ++x)
		{
			SERIAL.print("A");
			SERIAL.flush();	   
			myDelayMs(500);
		}
	#endif

	//************************

	#if ERROR_CHECKING == 4
		// rtos tasks should not reach the end of their function
		// if you reach the end they must deleting themselves
		// this will cause a crash
		// cause a rtosFatalError
	#else
		// delete ourselves.
		// Have to call this or the system crashes when you reach the end bracket and then get scheduled.
		SERIAL.println("Thread A: Deleting");
		vTaskDelete( NULL );
	#endif
}

//*****************************************************************
// Create a thread that prints out B to the screen every second
// this task will run forever
//*****************************************************************
static void threadB( void *pvParameters ) 
{
  SERIAL.println("Thread B: Started");

  while(1)
  {
    SERIAL.println("B");
	SERIAL.flush();			   
    myDelayMs(2000);
  }

}

//*****************************************************************
// Task will periodically print out useful information about the tasks running
// Is a useful tool to help figure out stack sizes being used
// Run time stats are generated from all task timing collected since startup
// No easy way yet to clear the run time stats yet
//*****************************************************************
static char ptrTaskList[400]; //temporary string buffer for task stats

void taskMonitor(void *pvParameters)
{
    int x;
    int measurement;
    
    SERIAL.println("Task Monitor: Started");

    // run this task afew times before exiting forever
    while(1)
    {
    	myDelayMs(10000); // print every 10 seconds

    	SERIAL.flush();
		SERIAL.println("");			 
    	SERIAL.println("****************************************************");
    	SERIAL.print("Free Heap: ");
    	SERIAL.print(xPortGetFreeHeapSize());
    	SERIAL.println(" bytes");

    	SERIAL.print("Min Heap: ");
    	SERIAL.print(xPortGetMinimumEverFreeHeapSize());
    	SERIAL.println(" bytes");
    	SERIAL.flush();

    	SERIAL.println("****************************************************");
    	SERIAL.println("Task            ABS             %Util");
    	SERIAL.println("****************************************************");

    	vTaskGetRunTimeStats(ptrTaskList); //save stats to char array
    	SERIAL.println(ptrTaskList); //prints out already formatted stats
    	SERIAL.flush();

		SERIAL.println("****************************************************");
		SERIAL.println("Task            State   Prio    Stack   Num     Core" );
		SERIAL.println("****************************************************");

		vTaskList(ptrTaskList); //save stats to char array
		SERIAL.println(ptrTaskList); //prints out already formatted stats
		SERIAL.flush();

		SERIAL.println("****************************************************");
		SERIAL.println("[Stacks Free Bytes Remaining] ");

		measurement = uxTaskGetStackHighWaterMark( Handle_aTask );
		SERIAL.print("Thread A: ");
		SERIAL.println(measurement);

		measurement = uxTaskGetStackHighWaterMark( Handle_bTask );
		SERIAL.print("Thread B: ");
		SERIAL.println(measurement);

		measurement = uxTaskGetStackHighWaterMark( Handle_monitorTask );
		SERIAL.print("Monitor Stack: ");
		SERIAL.println(measurement);

		SERIAL.println("****************************************************");
		SERIAL.flush();

    }

    // delete ourselves.
    // Have to call this or the system crashes when you reach the end bracket and then get scheduled.
    SERIAL.println("Task Monitor: Deleting");
    vTaskDelete( NULL );

}


//*****************************************************************

void setup() 
{

  SERIAL.begin(115200);

  delay(1000); // prevents usb driver crash on startup, do not omit this
  while (!SERIAL) ;  // Wait for serial terminal to open port before starting program

  SERIAL.println("");
  SERIAL.println("******************************");
  SERIAL.println("        Program start         ");
  SERIAL.println("******************************");
  SERIAL.flush();			 

  // Set the led the rtos will blink when we have a fatal rtos error
  // RTOS also Needs to know if high/low is the state that turns on the led.
  // Error Blink Codes:
  //    3 blinks - Fatal Rtos Error, something bad happened. Think really hard about what you just changed.
  //    2 blinks - Malloc Failed, Happens when you couldn't create a rtos object. 
  //               Probably ran out of heap.
  //    1 blink  - Stack overflow, Task needs more bytes defined for its stack! 
  //               Use the taskMonitor thread to help gauge how much more you need
  vSetErrorLed(ERROR_LED_PIN, ERROR_LED_LIGHTUP_STATE);

  // sets the serial port to print errors to when the rtos crashes
  // if this is not set, serial information is not printed by default
  vSetErrorSerial(&SERIAL);

  // Create the threads that will be managed by the rtos
  // Sets the stack size and priority of each task
  // Also initializes a handler pointer to each task, which are important to communicate with and retrieve info from tasks
  xTaskCreate(threadA,     "Task A",       256, NULL, tskIDLE_PRIORITY + 3, &Handle_aTask);
  xTaskCreate(threadB,     "Task B",       256, NULL, tskIDLE_PRIORITY + 2, &Handle_bTask);
  xTaskCreate(taskMonitor, "Task Monitor", 256, NULL, tskIDLE_PRIORITY + 1, &Handle_monitorTask);

  #if ERROR_CHECKING == 5
	// cause a rtos malloc fail, not enough heap
	xTaskCreate(threadA,   "Task Fail",    9000, NULL, tskIDLE_PRIORITY + 4, &Handle_aTask);
  #endif


  #if ERROR_CHECKING == 6
	  // this error is you dont have enough ram for global memory objects and the heap
	  // this simulates program allocating alot of objects to memory at startup it cannot actually fit
	  // this is not caught by the rtos and system crashes at startup
	  // look at Basic_RTOS_Example2 example and the MemoryFree library to help discover these problems
	  // could try shrinking the heap in FreeRtosConfig.h (less room for rtos objects tho)
	  // or reduce the amount of library objects or globals being used
	  #define ARRAY_SIZE_GLOBAL	100000
	  long massiveArray[ARRAY_SIZE_GLOBAL];
	  long sum;
	  for(long x=1; x<ARRAY_SIZE_GLOBAL-1; ++x)
	  {
		sum = massiveArray[x] + massiveArray[x+1];
	  }
	  SERIAL.println(sum);
  #endif

  // Start the RTOS, this function will never return and will schedule the tasks.
  vTaskStartScheduler();

  // error scheduler failed to start
  // should never get here
  while(1)
  {
	SERIAL.println("Scheduler Failed! \n");
	SERIAL.flush();		  
	delay(1000);
  }

}

//*****************************************************************
// This is now the rtos idle loop
// No rtos blocking functions allowed!
//*****************************************************************
void loop() 
{
    // Optional commands, can comment/uncomment below
    SERIAL.print("."); //print out dots in terminal, we only do this when the RTOS is in the idle state
	SERIAL.flush();			   
    delay(100); //delay is interrupt friendly, unlike vNopDelayMS
}


//*****************************************************************

