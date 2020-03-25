
#include "runTimeStats_hooks.h"

//************************************************************************

// setup the hardware timer to use as a counter
void vMainConfigureTimerForRunTimeStats( void )
{
	// do nothing, will use the arduino systick timer
	// can change this if you want
}

// will return the counter value to generate run time stats
unsigned long ulMainGetRunTimeCounterValue( void )
{
  return micros(); //use already setup arduino systick timer
}

//************************************************************************

