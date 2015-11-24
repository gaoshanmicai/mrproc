#include "main.h"
void queue_in_buf(unsigned char in)
{
	//RF_DATA.rear++;
	if(!BC_DATA.rf_que[BC_DATA.rear])
	{
		BC_DATA.rf_que[BC_DATA.rear++] = in;
	}
//	RF_DATA.rear++;
	if(BC_DATA.rear > 199)
	{
		if(BC_DATA.front != 0)
		{
			BC_DATA.rear = 0;
			BC_DATA.rf_que[BC_DATA.rear] = 0;
		}
		else
		{
			BC_DATA.rear--;
			BC_DATA.rf_que[BC_DATA.rear] = 0;
		}
	}
	else
	{
		if(BC_DATA.rear == BC_DATA.front)
		{
			BC_DATA.rear--;
			BC_DATA.rf_que[BC_DATA.rear] = 0;
		}
	}
}

unsigned char queue_out_buf(void)
{
	unsigned char return_data;
	return_data = BC_DATA.rf_que[BC_DATA.front];
	BC_DATA.rf_que[BC_DATA.front++] = 0;
	if(BC_DATA.front > 199)
	{
		if(BC_DATA.rear != 199)
		{
			BC_DATA.front = 0;
		}
		else
		{
			BC_DATA.front = BC_DATA.rear;
		}
	}
	else
	{
		if(BC_DATA.front-1 == BC_DATA.rear)
		{
			BC_DATA.front = BC_DATA.rear;
		}
	}
	return return_data;
}

/*
void queue_in_buf(unsigned char in)
{
	//RF_DATA.rear++;
	if(!BC_DATA.rf_que[BC_DATA.rear])
	{
		BC_DATA.rf_que[BC_DATA.rear++] = in;
		if(BC_DATA.rear > 199)
		{
			if(BC_DATA.front != 0)
			{
				BC_DATA.rear = 0;
			}
			else
			{
				BC_DATA.rear--;
	//			BC_DATA.rf_que[BC_DATA.rear] = 0;
			}
				BC_DATA.rf_que[BC_DATA.rear] = 0;
		}
		else
		{
			if(BC_DATA.rear == BC_DATA.front)
			{
				BC_DATA.rear--;
				BC_DATA.rf_que[BC_DATA.rear] = 0;
			}
		}
	}
//	RF_DATA.rear++;
}

unsigned char queue_out_buf(void)
{
	unsigned char return_data;
	return_data = BC_DATA.rf_que[BC_DATA.front];
	BC_DATA.rf_que[BC_DATA.front++] = 0;
	if(BC_DATA.front > 199)
	{
		BC_DATA.front = 0;

	}
	else
	{
		if(BC_DATA.front-1 == BC_DATA.rear)
		{
			BC_DATA.front = BC_DATA.rear;
		}
	}
	return return_data;
}*/
void queue_bc_reset(void)
{
	while(queue_out_buf());
}
//------ FOR UART0 ---------------------------------------------------
void queue_in_buf0(unsigned char in)
{
	//RF_DATA.rear++;
	if(!IP_DATA.rf_que[IP_DATA.rear])
	{
		IP_DATA.rf_que[IP_DATA.rear++] = in;
		if(IP_DATA.rear > 199)
		{
			if(IP_DATA.front != 0)
			{
				IP_DATA.rear = 0;
				IP_DATA.rf_que[IP_DATA.rear] = 0;
			}
			else
			{
				IP_DATA.rear--;
				IP_DATA.rf_que[IP_DATA.rear] = 0;
			}
		}
		else
		{
			if(IP_DATA.rear == IP_DATA.front)
			{
				IP_DATA.rear--;
				IP_DATA.rf_que[IP_DATA.rear] = 0;
			}
		}
	}
//	RF_DATA.rear++;
}

unsigned char queue_out_buf0(void)
{
	unsigned char return_data;
	return_data = IP_DATA.rf_que[IP_DATA.front];
	IP_DATA.rf_que[IP_DATA.front++] = 0;
	if(IP_DATA.front > 199)
	{
		if(IP_DATA.rear != 199)
		{
			IP_DATA.front = 0;
		}
		else
		{
			IP_DATA.front = IP_DATA.rear;
		}
	}
	else
	{
		if(IP_DATA.front-1 == IP_DATA.rear)
		{
			IP_DATA.front = IP_DATA.rear;
		}
	}
	return return_data;
}

/*void queue_reset(void)
{
	IP_DATA.front = IP_DATA.rear = 0;
}*/
