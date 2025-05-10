/*
 * InterruptHandler.h
 *
 * Created: 2022-03-08 14:54:03
 *  Author: simeng-0
 */ 


#ifndef INTERRUPTHANDLER_H_
#define INTERRUPTHANDLER_H_

#include "avr/io.h"
#include "TinyTimber.h"
#include <avr/interrupt.h>
#include "Backend.h"


#define initHandler(b) { initObject(), b }

typedef struct{
	Object super;
	Backend *backend;
}InterruptHandler;

void receiveInterrupt(InterruptHandler *self);
void transmitInterrupt(InterruptHandler *self);
void regEmptyInterrupt(InterruptHandler *self);


#endif /* INTERRUPTHANDLER_H_ */