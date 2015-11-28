/************************************************************************************** 
*   ����    ��2015��11��24�� (��Ȩ���У�����ؾ�) 
*   Ŀ��    ��ARM Cortex-M0 LPC1114 
*   ���뻷����KEIL 5.13
*   �ⲿ����12Mhz(��Ƶ50M)
*   ����    ��ѧ��ʹ�ô����ж�,ѧϰ���ڱ��
*   ����    ��Yuan

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
/*               ������                       */
/**********************************************/
int main()
{
	UART_init(9600); // �Ѵ��ڲ���������Ϊ115200
	LPC_UART->IER = 0x01;  // ���������ж�
	NVIC_EnableIRQ(UART_IRQn); // �������ж�
	led_init();
	Timer0_Intr_Config();
	ADC_Init();
	

	SCB->SCR = SCB->SCR |0x2;    //����˯��״̬

	
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

	
	







