/************************************************************************************** 
*   日期    ：2015年11月24日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 5.13
*   外部晶振：12Mhz(主频50M)
*   功能    ：学会使用串口中断,学习串口编程
*   作者    ：Yuan

**************************************************************************************/

#include "main.h"


uint8_t rec_buf;
rf_data_str BC_DATA;
rf_data_str IP_DATA;


uint8_t buffer[30];
uint8_t len;
void Timer0_Intr_Config(void);//Set I/O pin connected to LED as output
uint32_t value;

uint8_t commd[8]={0xbb,0x0,0x05,0x00,0x00,0x00,0x00,0x7e};



/**********************************************/
/*               主函数                       */
/**********************************************/
int main()
{
	UART_init(9600); // 把串口波特率配置为115200
	LPC_UART->IER = 0x01;  // 开启接收中断
	NVIC_EnableIRQ(UART_IRQn); // 开串口中断
	led_init();
	Timer0_Intr_Config();
	ADC_Init();
	

	SCB->SCR = SCB->SCR |0x2;    //进入睡眠状态

	
	while(1)
	{
		__WFI();
	}

}

void Timer0_Intr_Config(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL= LPC_SYSCON->SYSAHBCLKCTRL |(1<<9);
	LPC_TMR32B0->TCR = 0;
	LPC_TMR32B0->PR = 0;
	LPC_TMR32B0->PC = 0;
	LPC_TMR32B0->TC = 0;
	LPC_TMR32B0->MR0 = 19999999;
	LPC_TMR32B0->MCR = 3;
	LPC_TMR32B0->TCR = 1;
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
	return ;
}

void TIMER32_0_IRQHandler(void)
{
	
	LPC_TMR32B0->IR   = LPC_TMR32B0->IR;
	LPC_GPIO1->MASKED_ACCESS[1<<1]=~LPC_GPIO1->MASKED_ACCESS[1<<1];
	
  value=ADC_Read();
	commd[4]=(value>>8)&0x3;
	commd[5]=(value)&0xff;
	
	UART_send(commd,(sizeof(commd)/sizeof(commd[0])));
	
	
	
	return;
	
}

	
	







