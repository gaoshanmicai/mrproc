#include "main.h"

#include<string.h>
#define EVENT_QUEUE_LENGTH 30

state_st state;

struct
  {
    uint8_t head;
    uint8_t tail;
    uint8_t queue[EVENT_QUEUE_LENGTH];
  }events={0,0};
                                                        
 void give_event(uint8_t event, uint8_t nomore)
  {
    if(events.tail==255)  // if it's end 
      return;
    if(nomore)  // no more needed
      {
	  	uint8_t ev=events.head;
        for(ev; ev!=events.tail; )
          {
           if(events.queue[ev]==event)  // return;
              return;
            if(++ev==EVENT_QUEUE_LENGTH)  // end of Queue
              ev=0;
          }
      }
    events.queue[events.tail++]=event;  // input the event
    if(events.tail==EVENT_QUEUE_LENGTH) // event tail 
      events.tail=0;
    if(events.tail==events.head) 
      {
        events.head=events.tail;
        events.tail=255;
      }  
  }

/*
 uint8_t del_event(uint8_t event)
  {
    if(events.tail==255)
      return 0;
    for(uint8_t ev=events.head; ev!=events.tail; )
      {
        if(events.queue[ev]==event)  // there is event
          {
            events.queue[ev]=0;  // delete
            return 1;
          }
        if(++ev==EVENT_QUEUE_LENGTH)  // e reset
          ev=0;
      }
    return 0;
  }
*/

uint8_t get_event()
  {
    uint8_t tmp;
    if(events.tail==255)
      {
        events.tail=events.head;
	   // limo_ctrl.error_handling(ERR_QUEUEFULL);	XYZ	
        return 0;
      }  
    if(events.head==events.tail) 
      return 0;
    tmp=events.queue[events.head++];
    if(events.head==EVENT_QUEUE_LENGTH)
      events.head=0;
    return tmp;
  }


