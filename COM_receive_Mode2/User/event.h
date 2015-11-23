//!-------------------------------------------------------------------
//! Copyright (C) 2007-2012 PHYCHIPS
//!
//! @file	event.h
//! @brief	simple event fifo
//! 
//! $Id: event.h 2217 2013-07-04 11:32:24Z sjpark $			
//!-------------------------------------------------------------------
//! History
//!-------------------------------------------------------------------
//! 2012/03/27	jsyi		initial release
//! 2012/05/24	jsyi		added event fifo

#ifndef EVENT_H
#define EVENT_H
#include "commontypes.h"

#define EVENT_NUM_MAX	(8)
#define SYSTEM_TICK_FREQ (1000)

typedef enum EVENT_TYPE
{
	EVENT_NONE  = 0,
	EVENT_ENTRY,
	EVENT_EXIT,
	EVENT_DONE,
	EVENT_CUSTOM_BASE
} EVENT_TYPE;

//!-------------------------------------------------------------------
//! EVENT
//!-------------------------------------------------------------------
struct EVENT;
typedef void(*event_handler)(struct EVENT e);
typedef uint8 EVENT_PARAM;
typedef struct EVENT
{
	event_handler handler;
	EVENT_PARAM param;
} EVENT;

typedef struct  event_list_item_type
{	
	EVENT e;
    struct event_list_item_type* next;
    struct event_list_item_type* prev;
} event_list_item_type;

//!-------------------------------------------------------------------                 
//! EVENT Timer
//!-------------------------------------------------------------------

#define EVENT_TIMER_LIST_ITEM_MAX			(EVENT_NUM_MAX - 1) 	// up to 32
#define EVENT_TIMER_STATE_STOPPED			(0)
#define EVENT_TIMER_STATE_RUNNING			(1)

typedef void(*event_timer_list_item_pf_type) (EVENT e);
typedef struct  event_timer_list_item_type
{	                
    uint8 state;
    uint64 ms;
	EVENT e;
    struct event_timer_list_item_type* next;
    struct event_timer_list_item_type* prev;
} event_timer_list_item_type;

//!-------------------------------------------------------------------
//! Fuction Definitions
//!-------------------------------------------------------------------
#ifdef __DEBUG__
extern uint8 event_debug_count;
#endif

extern volatile uint64 RFID_SYSTEM_TICK;
extern BOOL event_idle_sleep_enable;

void event_init(void);
void event_send(EVENT e);
void event_post(EVENT e);
void event_post_delayed(EVENT e, uint32 ms);
void event_dispatch(void);
void event_flush(event_handler h);
void event_timer_flush(event_handler h);
#endif


