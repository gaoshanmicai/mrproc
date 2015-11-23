#ifndef EVENT_H
#define EVENT_H

#include "lpc11xx.h"
typedef uint8_t event;
extern unsigned char get_event(void);
extern void give_event(unsigned char event, unsigned char nomore);
unsigned char del_event(unsigned char event);


typedef enum cntrl_event
{
	keyNone=0,
	_keyEnd,
	eventSpuOn=150,
	eventTimer500ms,
	eventTimer100ms,
	keyChargerStateOn,
	keyChargerStateFull,
	keyChargerStateOff,
	eventBatteryInfo,
	keyEng,
	keySystemInfo,
	keyBeepInfo,
	_eventEnd
}state_st;

extern state_st state;

#endif

