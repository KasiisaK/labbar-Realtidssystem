/*
 * Backend.h
 *
 * Created: 2022-03-10 14:40:33
 *  Author: simeng-0
 */ 


#ifndef BACKEND_H_
#define BACKEND_H_

#include <avr/io.h>
#include "TinyTimber.h"
#include "Road.h"
#include "GUI.h"

#define initBackend(g, r) { initObject(), g, r, 0, {'a', 'b', 'c'} }

typedef struct  {
	Object super;
	GUI *gui;
	Road *road;
	int writerIndex;
	char data[3];
} Backend;

void start(Backend *self);
void receiveN(Backend *self);
void receiveS(Backend *self);
void receiveNtoB(Backend *self);
void receiveStoB(Backend *self);
void receiveE(Backend *self);
void write(Backend *self);
//void transmit();
//void transmitNext();



#endif /* BACKEND_H_ */