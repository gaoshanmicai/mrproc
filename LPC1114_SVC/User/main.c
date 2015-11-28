/************************************************************************************** 
*   日期    ：2015年11月24日 (版权所有，翻版必究) 
*   目标    ：ARM Cortex-M0 LPC1114 
*   编译环境：KEIL 5.13
*   外部晶振：12Mhz(主频50M)
*   功能    ：学会使用串口中断,学习串口编程
*   作者    ：Yuan

**************************************************************************************/

#include "main.h"

int __svc(0x00) svc_service_add(int x, int y);
int __svc(0x01) svc_service_sub(int x, int y);
int __svc(0x02) svc_service_incr(int x);



void SVC_Handler_main(unsigned int *svc_args);


uint8_t rec_buf;
rf_data_str BC_DATA;
rf_data_str IP_DATA;


uint8_t buffer[30];
uint8_t len;
void Timer0_Intr_Config(void);//Set I/O pin connected to LED as output





/**********************************************/
/*               主函数                       */
/**********************************************/
int main()
{
	int x,y,z;
	char str[30];
	UART_init(9600); // 把串口波特率配置为115200
	LPC_UART->IER = 0x01;  // 开启接收中断
	NVIC_EnableIRQ(UART_IRQn); // 开串口中断
	led_init();
	//Timer0_Intr_Config();
	x = 3; y = 5;
	z = svc_service_add(x,y);
	
	sprintf(str,"3+5 = %d\n",z);
	
	UART_send((uint8_t *)str,strlen(str));
	
	memset(str,0,30);
	x = 9; y = 2;
	
	z = svc_service_sub(x,y);
		sprintf(str,"9-2 = %d\n",z);
	
	UART_send((uint8_t *)str,strlen(str));
	memset(str,0,30);
	
	x = 3;
	z = svc_service_incr(x);
	
		sprintf(str,"3++= %d\n",z);
	
	UART_send((uint8_t *)str,strlen(str));
	
	
	

	//SCB->SCR = SCB->SCR |0x2;    //进入睡眠状态

	
	while(1)
	{
		//__WFI();
//		memset(str,0,sizeof(str));
//		sprintf(str,"this is a test");
//		UART_send((uint8_t *)str,strlen(str));
	}

}

__asm  void SVC_Handler(void)
{
	MOVS  r0,#4
	MOV   r1,LR
	TST   r0,r1
	BEQ  stacking_used_MSP
	MRS   R0, PSP     ;  
	LDR   R1,=__cpp(SVC_Handler_main)
	BX    R1
stacking_used_MSP
	MRS  R0, MSP ;  
	LDR  R1,=__cpp(SVC_Handler_main)
	BX   R1
	
}
void Timer0_Intr_Config(void)
{
	LPC_SYSCON->SYSAHBCLKCTRL= LPC_SYSCON->SYSAHBCLKCTRL |(1<<9);
	LPC_TMR32B0->TCR = 0;
	LPC_TMR32B0->PR = 0;
	LPC_TMR32B0->PC = 0;
	LPC_TMR32B0->TC = 0;
	LPC_TMR32B0->MR0 = 5999999;
	LPC_TMR32B0->MCR = 3;
	LPC_TMR32B0->TCR = 1;
	NVIC_EnableIRQ(TIMER_32_0_IRQn);
	return ;
}

void TIMER32_0_IRQHandler(void)
{
	
	LPC_TMR32B0->IR   = LPC_TMR32B0->IR;
	LPC_GPIO1->MASKED_ACCESS[1<<1]=~LPC_GPIO1->MASKED_ACCESS[1<<1];
	
	return;
	
}


void SVC_Handler_main(unsigned int *svc_args)
{
	unsigned int svc_number;
	svc_number = ((char *)svc_args[6])[-2];
	switch(svc_number)
	{
		case 0:svc_args[0] = svc_args[0] + svc_args[1];
		break;
		case 1:svc_args[0] = svc_args[0] - svc_args[1];
		break;
		case 2:svc_args[0] = svc_args[0] + 1;
		break;
		default: //Unknow SVC request
			break;
	}
	
	return ;
	
	
	
}
	
	







