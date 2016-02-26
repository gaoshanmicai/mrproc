#include "lpc11xx.h"
#include "main.h"

uint8_t chr;

#define RECEIVE_BUF_LENGTH 136
volatile uint8_t receive_bufs[RECEIVE_BUF_LENGTH];


/************************************************/
/* �������ܣ���ʼ��UART��                       */
/************************************************/
void UART_init(uint32_t baudrate)
{
	uint32_t DL_value,Clear=Clear;   // (�����ַ�ʽ������������������Warning)                       
	
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<16); // ʹ��IOCONʱ�� 
	LPC_IOCON->PIO1_6 &= ~0x07;    
	LPC_IOCON->PIO1_6 |= 0x01; //��P1.6������ΪRXD
	LPC_IOCON->PIO1_7 &= ~0x07;	
	LPC_IOCON->PIO1_7 |= 0x01; //��P1.7������ΪTXD
	LPC_SYSCON->SYSAHBCLKCTRL &= ~(1<<16); // ����IOCONʱ��

	LPC_SYSCON->UARTCLKDIV = 0x1;	//ʱ�ӷ�ƵֵΪ1
	LPC_SYSCON->SYSAHBCLKCTRL |= (1<<12);//����UARTʱ��
	LPC_UART->LCR = 0x83;   //8λ���䣬1��ֹͣλ���޼�żУ�飬������ʳ���������
	DL_value = SystemCoreClock/16/baudrate ;  //����ò�����Ҫ��ĳ�������Ĵ���ֵ
	LPC_UART->DLM = DL_value / 256;	   //д������������λֵ			
	LPC_UART->DLL = DL_value % 256;	  //д������������λֵ
	LPC_UART->LCR = 0x03;    //DLAB��0
	LPC_UART->FCR = 0x07;    //����FIFO�����RxFIFO �� TxFIFO
	Clear = LPC_UART->LSR;   //��UART״̬�Ĵ�������ղ���״̬
}

/************************************************/
/* �������ܣ����ڽ����ֽ�����                       */
/************************************************/
uint8_t UART_recive(void)
{	
	while(!(LPC_UART->LSR & (1<<0)));//�ȴ����յ�����
	return(LPC_UART->RBR);			 //��������
}

/************************************************/
/* �������ܣ����ڷ����ֽ�����                       */
/************************************************/
void UART_send_byte(uint8_t byte)
{
	LPC_UART->THR = byte;
	while ((LPC_UART->LSR & (1<<5))!=(1<<5));//�ȴ�������
}

/************************************************/
/* �������ܣ����ڷ�����������                   */
/************************************************/
void UART_send(uint8_t *Buffer, uint32_t Length)
{
	while(Length != 0)
	{
		while ( !(LPC_UART->LSR & (1<<5)) );//�ȴ�������
		LPC_UART->THR = *Buffer;
		Buffer++;
		Length--;
	}
}


/***********************************/
/* �������ƣ������жϺ���          */
/***********************************/
void UART_IRQHandler(void)
{
	uint32_t IRQ_ID;		  // �����ȡ�ж�ID�ű���
	uint8_t rec_buf;    // ����������ݱ�������
	EVENT  e;
	static int i=0;

	IRQ_ID = LPC_UART->IIR;   // ���ж�ID��
	IRQ_ID =((IRQ_ID>>1)&0x7);// ���bit3:bit1	
	if(IRQ_ID == 0x02 )		  // ����ǲ��ǽ�������������ж�
	{
			rec_buf = LPC_UART->RBR;
		  //queue_in_buf0(rec_buf);
		  if(rec_buf ==0x55)
			{
				e.param = i;
				
			
		  	e.handler = led_on;
					event_send(e);
			}
		  	else if(rec_buf ==0x66)
				{
					e.param = i;
				e.handler = led_off;
						event_send(e);
					
				}
				else if(rec_buf ==0x77)
				{
					 i++;
					if(i >3)
						i = 0;
				}
			
			
				//(i%2==0)?(e.handler = led_on):(e.handler = led_off);
			  
		
				
			
			
				
			//UART_send_byte(rec_buf); // �ѽ��յ����ֽڷ��ش���
	}
}


void Recieve_exe(void)
{
	chr = queue_out_buf0();	
	
	give_event(chr,0);
	
}



