#include "delay.h"
#include "rcp_event.h"



void HAL_Delay(__IO uint32_t Delay)
{
	uint32_t stick;
	
  stick = msTicks;
	
	while( msTicks-stick <Delay);
	
	
}


