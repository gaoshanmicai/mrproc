#include"main.h"

uint8_t buf2[40];
uint8_t buf2_len;

void get_dataCtrl(unsigned char eve)
{
	switch(chr)
	{
		case keyNone:
			
			state = _keyEnd;
		  UART_send((uint8_t *)&state,1);
		  chr =0xff;
		break;
		case  _keyEnd:

			state = eventSpuOn;
		  UART_send((uint8_t *)&state,1);
		  chr =0xff;
		break;
		case  eventSpuOn:
			
			state = _keyEnd;
		  UART_send((uint8_t *)&state,1);
		  chr =0xff;
		break;
		default:break;
		
		
		
		
		
		
	}

}


void execute_rs232()
{
	switch(chr)
	{
		case keyNone:
				buf2_len=sprintf((char*)buf2,"the event is %d\n",state);
		
		UART_send((uint8_t *)&buf2,buf2_len);
		  
		break;
		case  _keyEnd:
				buf2_len=sprintf((char*)buf2,"the event is %d\n",state);
		
		UART_send((uint8_t *)&buf2,buf2_len);
			
		break;
		case  eventSpuOn:
				buf2_len=sprintf((char*)buf2,"the event is %d\n",state);
		
		UART_send((uint8_t *)&buf2,buf2_len);
		break;
		
		
	
		
		
	}
}

