/*
 * USART.h
 *
 * Created: 10/03/2025 11:21:50
 *  Author: AskFr
 */ 

#ifndef USART_H
#define USART_H

#include "TinyTimber.h"
#include "backend.h"

typedef struct {
	Object super;
	Backend *backRef;
} USART;

void usart_init(USART *self);
unsigned char USART_Receive(void);
void mainUSARTLoop(USART *self);

#define initUSART(backEnd) { initObject(), backEnd}

#endif