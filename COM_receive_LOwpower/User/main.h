#ifndef _MAIN_H
#define _MAIN_H
#include "lpc11xx.h"
#include "string.h"
#include "stdio.h"
#include "queue.h"
#include "event.h"
#include "uart.h"
#include "ctrl.h"
#include "led.h"
#include "adc.h"

typedef unsigned char uint8_t;
typedef unsigned int  uint32_t;
typedef unsigned short int uint16_t;

typedef struct {
	unsigned char front;
	unsigned char rear;
	unsigned char rf_que[250];
} rf_data_str;


extern rf_data_str BC_DATA;
extern rf_data_str IP_DATA;



#endif


