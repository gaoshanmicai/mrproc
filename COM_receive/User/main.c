/************************************************************************************** 
*   日期    ：2013年11月6日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 5.13
*   外部晶振：10Mhz(主频50M)
*   功能    ：学会使用串口中断,学习串口编程
*   作者    ：Yuan

**************************************************************************************/

#include "main.h"


uint8_t rec_buf;
rf_data_str BC_DATA;
rf_data_str IP_DATA;


uint8_t buffer[30];
uint8_t len;




/**********************************************/
/*               主函数                       */
/**********************************************/
int main()
{
	UART_init(9600); // 把串口波特率配置为115200
	LPC_UART->IER = 0x01;  // 开启接收中断
	NVIC_EnableIRQ(UART_IRQn); // 开串口中断
	led_init();
	
	memset(&IP_DATA.rf_que[0],0,200);
	IP_DATA.front = 0;
	IP_DATA.rear = 0;
	memset(&BC_DATA.rf_que[0],0,200);
	BC_DATA.front = 0;
	BC_DATA.rear = 0;
	
	state =keyNone;
	
	give_event(keyNone,0);
	
	 //execute_rs232();
	len=sprintf((char*)buffer,"this is the start");
		
		UART_send(buffer,len);
	
	while(1)
	{
		event evls = get_event();
		get_dataCtrl(evls);
	  //execute_rs232();
		
		
		if(IP_DATA.front != IP_DATA.rear || (IP_DATA.front == IP_DATA.rear && IP_DATA.rf_que[IP_DATA.front]))
		{
			Recieve_exe();
		}
		
		LED1_ON;
		LED2_OFF;
		delay();
		LED1_OFF;
		LED2_ON;
		delay();
	}
}







