#ifndef _DELAY_H
#define _DELAY_H

#include "LPC11xx.h"

extern volatile uint32_t msTicks;
extern void HAL_Delay(__IO uint32_t Delay);
#endif


