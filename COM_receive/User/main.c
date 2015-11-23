/************************************************************************************** 
*   ����    ��2013��11��6�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 5.13
*   �ⲿ����10Mhz(��Ƶ50M)
*   ����    ��ѧ��ʹ�ô����ж�,ѧϰ���ڱ��
*   ����    ��Yuan

**************************************************************************************/

#include "main.h"


uint8_t rec_buf;
rf_data_str BC_DATA;
rf_data_str IP_DATA;


uint8_t buffer[30];
uint8_t len;




/**********************************************/
/*               ������                       */
/**********************************************/
int main()
{
	UART_init(9600); // �Ѵ��ڲ���������Ϊ115200
	LPC_UART->IER = 0x01;  // ���������ж�
	NVIC_EnableIRQ(UART_IRQn); // �������ж�
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







