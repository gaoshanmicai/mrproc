#ifndef _ADC_H
#define _ADC_H
#include "lpc11xx.h"
#define  Vref   3300


extern void ADC_Init(void);
extern uint16_t ADC_Read(void);   // ��ȡ��ѹֵ��AD0��


#endif


