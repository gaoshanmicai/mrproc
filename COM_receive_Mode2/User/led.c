#include "main.h"

/***********************************/
/* ????:LED????           */
/***********************************/
void led_init()
{
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // ??IOCON?? 

	LPC_IOCON->R_PIO1_1 &= ~0x07;	
	LPC_IOCON->R_PIO1_1 |= 0x01; //?P1.1????GPIO
	LPC_IOCON->R_PIO1_2   &=  ~0x07; 
	LPC_IOCON->R_PIO1_2   |=  0x01; 
//	LPC_IOCON->PIO1_6   &=  ~0x07; 
//	LPC_IOCON->PIO1_6   |=  0x00; 
//	LPC_IOCON->PIO1_7   &=  ~0x07; 
//	LPC_IOCON->PIO1_7   |=  0x00; 
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // ??IOCON??
	

	LPC_GPIO1->DIR |= (1<<1); // ?P1.1???????
	LPC_GPIO1->DATA |= (1<<1); // ?P1.1??????
	LPC_GPIO1->DIR |= (1<<2); // ?P1.1???????
	LPC_GPIO1->DATA |= (1<<2); // ?P1.1??????
//	LPC_GPIO1->DIR |= (1<<6); // ?P1.1???????
//	LPC_GPIO1->DATA |= (1<<6); //?P1.1??????
//	LPC_GPIO1->DIR |= (1<<7); // ?P1.1???????
//	LPC_GPIO1->DATA |= (1<<7); // ?P1.1??????
}

void LED_ON(uint8_t val)
{
//  uint8_t value;
//  if(value/1 !=0)
//   LPC_GPIO1->DATA &= ~(1<<1);
//  else
//    LPC_GPIO1->DATA |= (1<<1);
//   value>>1;
//   if(value/1 !=0)
//   LPC_GPIO1->DATA &= ~(1<<2);
//  else
//    LPC_GPIO1->DATA |= (1<<2);
//	value>>1;
//	  if(value/1 !=0)
//   LPC_GPIO1->DATA &= ~(1<<6);
//  else
//    LPC_GPIO1->DATA |= (1<<6);
//		value>>1;
//	  if(value/1 !=0)
//   LPC_GPIO1->DATA &= ~(1<<7);
//  else
//    LPC_GPIO1->DATA |= (1<<7);
}




/***********************************/
/* Delay            */
/***********************************/
void delay()
{
	uint16_t i,j;
	
	for(i=0;i<100;i++)
		for(j=0;j<20000;j++);
}


