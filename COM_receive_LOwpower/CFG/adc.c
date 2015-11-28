#include "adc.h"
#include "lpc11xx.h"
void ADC_Init(void)
{
	LPC_SYSCON->PDRUNCFG &= ~(0x1<<4);
	LPC_SYSCON->SYSAHBCLKCTRL  |= (1<<13);
	LPC_SYSCON->SYSAHBCLKCTRL  |=(1<<16);
	
	LPC_IOCON->R_PIO0_11 &=~0x7;
	LPC_IOCON->R_PIO0_11 |=0x02;
	LPC_IOCON->R_PIO0_11 &=~(3<<3);
	LPC_IOCON->R_PIO0_11 &=~(1<<7);
	
	LPC_SYSCON->SYSAHBCLKCTRL &=~(1<<16);
	LPC_ADC->CR = (1<<0)\
	              |(6<<8);

	
}

uint16_t ADC_Read(void)
{
	uint32_t adc_value=0;

	LPC_ADC->CR |= (1<<24); //?
	while((LPC_ADC->DR[0]&0x80000000)==0);
	adc_value = (LPC_ADC->DR[0]>>6)&0x3FF;		
	//adc_value = (adc_value*Vref)/1024; //
	
	

	return adc_value;	  // ????
}
