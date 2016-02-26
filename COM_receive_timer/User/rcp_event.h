#ifndef _RCP_EVENT_H
#define _RCP_EVENT_H
#include "LPC11xx.h"
#include "stdbool.h"


#define EVENT_NUM_MAX (8)

typedef enum EVENT_TYPE
{
	
	EVENT_NONE = 0,
	EVENT_ENTRY,
	EVENT_EXIT,
	EVENT_DONE,
	EVENT_CUSTOM_BASE
}EVENT_TYPE;


struct EVENT;
typedef void(*event_handler)(struct EVENT e);
typedef uint8_t EVENT_PARAM;


typedef struct EVENT
{
	event_handler handler;
	EVENT_PARAM param;
}EVENT;

typedef struct event_list_item_type
{
	EVENT e;
	struct event_list_item_type *next;
	struct event_list_item_type *prev;
}event_list_item_type;


#define EVENT_TIMER_LIST_ITEM_MAX  (EVENT_NUM_MAX-1)
#define EVENT_TIMER_STATE_STOPPED   (0)
#define EVENT_TIMER_STATE_RUNNING    (1)

typedef void(*event_timer_list_item_pf_type)(EVENT e);

typedef struct  event_timer_list_item_type
{	                
    uint8_t state;
    uint64_t ms;
	EVENT e;
    struct event_timer_list_item_type* next;
    struct event_timer_list_item_type* prev;
} event_timer_list_item_type;


extern volatile uint64_t RFID_SYSTEM_TICK;
extern bool event_idle_sleep_enable;

void event_init(void);
void event_send(EVENT e);
void event_post(EVENT e);
void event_post_delayed(EVENT e, uint32_t ms);
void event_dispatch(void);
void event_flush(event_handler h);
void event_timer_flush(event_handler h);


#endif


