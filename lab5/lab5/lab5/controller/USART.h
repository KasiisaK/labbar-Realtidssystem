/*
 * USART.h
 *
 * Created: 10/03/2025 11:21:50
 *  Author: AskFr
 */ 

#ifndef USART_H
#define USART_H

#include "TinyTimber.h"
#include "TrafficLight.h"

typedef struct {
	Object super;
	TrafficLight *trafficLight; 
} USART;

void usart_init(USART *self);  
void usart_send(USART *self, uint8_t data); 

#define initUSART(tl) { initObject(), tl }

#endif