//!-------------------------------------------------------------------
//! Copyright (C) 2007-2012 PHYCHIPS
//!
//! @file	event.c
//! @brief	simple event fifo
//! 
//! $Id: event.c 2217 2013-07-04 11:32:24Z sjpark $			
//!-------------------------------------------------------------------
//! History
//!-------------------------------------------------------------------
//! 2012/03/27	jsyi		initial release
//! 2012/05/24	jsyi		added event fifo

#include "lpc11xx.h"
//#include "timer.h"
//#include "hal.h"
#include "event.h"

//!-------------------------------------------------------------------
//! Definitions
//!-------------------------------------------------------------------
volatile uint64 RFID_SYSTEM_TICK = 0;
BOOL event_idle_sleep_enable = FALSE;

#ifdef __DEBUG__
uint8 event_debug_count = 0;
/*
uint32 timer_s = 0;
uint32 timer_e = 0;
uint32 timer_d = 0;
*/
#endif

//#define	EVENT_TIMER_IRQ		TIMER0_IRQn	 
//#define	EVENT_TIMER			TIMER0

event_timer_list_item_type	event_timer_list[EVENT_TIMER_LIST_ITEM_MAX] = {0,};
event_timer_list_item_type*	event_timer_list_head = NULL;

event_list_item_type		event_list[EVENT_NUM_MAX] = {0,};
event_list_item_type		*event_list_tail = NULL;
event_list_item_type		*event_list_head = NULL;



void event_timer_irq_handler(void);
void event_init(void)
{	
	// System Tick
	SysTick_Config(SystemCoreClock / SYSTEM_TICK_FREQ);
}

//!---------------------------------------------------------------
//!	@brief
//!		SysTick Handler
//!
//! @param
//!		None
//!
//! @return
//!		None
//!
//!---------------------------------------------------------------
#ifdef __FEATURE_BOOTLOADER__
void _SysTick_Handler(void)
#else
void SysTick_Handler(void)
#endif
{ 
    RFID_SYSTEM_TICK++;
	
	if( (NULL != event_timer_list_head)
		&& (event_timer_list_head->ms <= RFID_SYSTEM_TICK) )
	{
		event_timer_irq_handler();
	}
}


//!---------------------------------------------------------------
//!	@brief
//!		Adds a timer list item
//!
//! @param
//!		id: specify a software timer
//!
//! @return
//!		None
//!
//!---------------------------------------------------------------
static void event_timer_add(event_timer_list_item_type *new_node)
{
	if(NULL == event_timer_list_head)
	{
		event_timer_list_head = new_node;
	}
	else
	{
		event_timer_list_item_type*	pnode;

		pnode = event_timer_list_head;	

		while(NULL != pnode)
		{
			if(pnode->ms > new_node->ms)
			{
				if(NULL != pnode->prev) // mid
				{
					new_node->next = pnode;
					new_node->prev = pnode->prev;					
					pnode->prev->next = new_node;
					pnode->prev = new_node;
				}
				else // first
				{
					new_node->next =  pnode;
					pnode->prev = new_node;
					event_timer_list_head = new_node;
				}

				break;
			}
			else if((pnode->ms <= new_node->ms) && (NULL == pnode->next)) // last
			{
				pnode->next = new_node;
				new_node->prev = pnode;

				break;
			}

			pnode = pnode->next;
		}
	}

	
}


//!---------------------------------------------------------------
//!	@brief
//!		frees the node
//!
//! @param
//!		id: specify	a software timer
//!
//! @return
//!		None
//!
//!---------------------------------------------------------------
static void event_timer_free(event_timer_list_item_type *rnode)
{
	if( (NULL == rnode->prev) && (NULL == rnode->next) )
	{
		event_timer_list_head = NULL;
	}
	else if(rnode->prev == NULL) // first
	{		
		event_timer_list_head = rnode->next;
		event_timer_list_head->prev = NULL;
		rnode->next = NULL;
	}	

	else if(rnode->next == NULL) // last
	{
		rnode->prev->next = NULL;
		rnode->prev = NULL;
	}
	else // mid
	{
		rnode->prev->next	=  rnode->next;
		rnode->next->prev	=  rnode->prev;
		rnode->prev = NULL;
		rnode->next = NULL;
	}
}




//!---------------------------------------------------------------
//!	@brief
//!		
//!
//! @param
//! 	
//!
//! @return
//!		
//!
//!---------------------------------------------------------------
void event_timer_irq_handler(void)
{		
	if(NULL != event_timer_list_head)
	{  	
		event_timer_list_item_type* pnode;

		event_timer_list_head->ms = 0;
		pnode = event_timer_list_head;

		while((NULL != pnode) && (0 == pnode->ms))
		{
			event_timer_free(pnode);
			
			if(NULL != pnode->e.handler)
			{
				event_post(pnode->e);
				pnode->e.handler = NULL;
			}

			pnode->state = EVENT_TIMER_STATE_STOPPED;
			pnode = event_timer_list_head;
		}
	}	
}

void event_timer_flush(event_handler h)
{
	if(NULL != event_timer_list_head)
	{  	
		event_timer_list_item_type* pnode;
		event_timer_list_item_type* pnext;
		pnode = event_timer_list_head;

		while((NULL != pnode))
		{			
			pnext = pnode->next;			
			if( h == pnode->e.handler )
			{
				event_timer_free(pnode);
				pnode->e.handler = NULL;
				pnode->ms = 0;
				pnode->state = EVENT_TIMER_STATE_STOPPED;	   
			}
			pnode = pnext;			
		}
	}
	
}


//!---------------------------------------------------------------
//!	@brief
//!		allocates a node
//!
//! @param
//! 	EVENT e:
//!		uint32 ms:
//!
//! @return
//!		a pointer to the allocated note
//!
//!---------------------------------------------------------------
static event_timer_list_item_type* event_timer_alloc_node
	(EVENT e, uint32 ms)
{
	uint8	i;
	event_timer_list_item_type* pnode;
	pnode = &event_timer_list[0];

	for(i=0; i<EVENT_TIMER_LIST_ITEM_MAX; i++)
	{			
		if(pnode->state == EVENT_TIMER_STATE_STOPPED)
		{				
			pnode->state = EVENT_TIMER_STATE_RUNNING;
			pnode->ms = (RFID_SYSTEM_TICK + ms);
			pnode->e = e;
			pnode->prev = NULL;
			pnode->next = NULL;
			return pnode;
		}
		pnode++;
	}		
	return NULL;
}


//!---------------------------------------------------------------
//!	@brief
//!		
//!
//! @param
//!		
//!		
//! @return
//!		
//!
//!---------------------------------------------------------------
void event_post_delayed(EVENT e, uint32 ms)
{
	event_timer_list_item_type* new_node;
	
	new_node = event_timer_alloc_node(e, ms);
	
	if(NULL == new_node) 
		return;

	event_timer_add(new_node);	
}

//!---------------------------------------------------------------
//!	@brief
//!		
//!
//! @param
//! 	
//!
//! @return
//!		
//!
//!---------------------------------------------------------------
static event_list_item_type* event_alloc_node(void)	
{
	uint8 i;
	
	for(i = 0; i < EVENT_NUM_MAX; i++)
	{		
		if( (event_list[i].e.handler == NULL) && (event_list[i].e.param == 0) )
		{
#ifdef __DEBUG__		
			event_debug_count++;
#endif			
			return &event_list[i];
		}
	}

	return NULL;
}


//!---------------------------------------------------------------
//!	@brief
//!		
//!
//! @param
//! 	
//!
//! @return
//!		
//!
//!---------------------------------------------------------------
void event_post(EVENT e)
{		
	if(e.handler != NULL)
	{
		event_list_item_type *pnode;

		__disable_irq();		
		pnode = event_alloc_node();
				
		if(pnode != NULL)
		{	
			pnode->e = e;

			if( event_list_tail == NULL)
			{
				event_list_head = pnode;
				event_list_tail = pnode;
			}
			else
			{
				pnode->prev = event_list_tail;
				event_list_tail->next = pnode;
 				event_list_tail = pnode;
			}	
			
		}
		__enable_irq();
 
	}
	
}


//!---------------------------------------------------------------
//!	@brief
//!		
//!
//! @param
//! 	
//!
//! @return
//!		
//!
//!---------------------------------------------------------------
void event_send(EVENT e)
{		
	if(e.handler != NULL)
	{
		event_list_item_type *pnode;
		
		__disable_irq();
		pnode = event_alloc_node();
		if(pnode != NULL)
		{
			pnode->e = e;

			if( event_list_head == NULL)
			{
				event_list_head = pnode;
				event_list_tail = pnode;
			}
			else				
			{
				event_list_head->prev = pnode;
				pnode->next = event_list_head;
				event_list_head = pnode;
			}
		}
		__enable_irq();
			
	}

	
}


//!---------------------------------------------------------------
//!	@brief
//!		frees the node
//!
//! @param
//!		id: specify	a software timer
//!
//! @return
//!		None
//!
//!---------------------------------------------------------------
static void event_fifo_free(event_list_item_type *rnode)
{
	if( (NULL == rnode->prev) && (NULL == rnode->next) )
	{
		event_list_head = NULL;
		event_list_tail = NULL;
	}
	else if(rnode->prev == NULL) // first
	{		
		event_list_head = rnode->next;
		event_list_head->prev = NULL;
		rnode->next = NULL;
	}
	else if(rnode->next == NULL) // last
	{
		event_list_tail = rnode->prev;
		event_list_tail->next = NULL;		
		rnode->prev = NULL;		
	}
	else // mid
	{
		rnode->prev->next	=  rnode->next;
		rnode->prev = NULL;
		rnode->next->prev	=  rnode->prev;
		rnode->next = NULL;
	}
}


void event_fifo_flush(event_handler h)
{

	if(NULL != event_list_head)
	{  	
		event_list_item_type* pnode;
		event_list_item_type* pnext;
		pnode = event_list_head;

		while((NULL != pnode))
		{			
			pnext = pnode->next;			
			if( h == pnode->e.handler )
			{
				event_fifo_free(pnode);
				pnode->e.handler = NULL;
				pnode->e.param = 0;
			}
			pnode = pnext; 
		}
	}
  	
}

//!---------------------------------------------------------------
//!	@brief
//!		
//!
//! @param
//! 	
//!
//! @return
//!		
//!
//!---------------------------------------------------------------

void event_flush(event_handler h)
{
	__disable_irq();
	// remove node
	event_fifo_flush(h);
	// remove node from event timer
	event_timer_flush(h);
	__enable_irq();	
}


//!---------------------------------------------------------------
//!	@brief
//!		
//!
//! @param
//! 	
//!
//! @return
//!		
//!
//!---------------------------------------------------------------
void event_idle(void)
{
	if(event_idle_sleep_enable) 
		//&& hal_pwrmgmt.pwr_mode <= PMODE_S2_IDLE)
		__WFI();
}

//!---------------------------------------------------------------
//!	@brief
//!		
//!
//! @param
//! 	
//!
//! @return
//!		
//!
//!---------------------------------------------------------------
void event_dispatch(void)
{		
	while(1) 
	{
 		if(event_list_head != NULL)
		{				
			event_list_item_type *pnode;

			// remove first node
			__disable_irq();
			pnode = event_list_head;
			event_fifo_free(pnode);		
			__enable_irq();
			pnode->e.handler(pnode->e);
			// clear node 
			pnode->e.handler = NULL;
			pnode->e.param = 0;
			
#ifdef __DEBUG__
			event_debug_count--;
#endif						
		}
		else
		{
			event_idle();
		}
	}
	
}


