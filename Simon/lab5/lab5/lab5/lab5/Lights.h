/*
 * Lights.h
 *
 * Created: 2022-03-08 14:57:30
 *  Author: simeng-0
 */ 


#ifndef LIGHTS_H_
#define LIGHTS_H_

#include "TinyTimber.h"
#include "avr/io.h"

#define initLights() { initObject(), 0, 0 }

typedef struct  {
	Object super;
	int northStatus;
	int southStatus;
} Lights;

void greenSouthBound(Lights *self);
void redSouthBound(Lights *self);
void greenNorthBound(Lights *self);
void redNorthBound(Lights *self);
void redBothDirections(Lights *self);



#endif /* LIGHTS_H_ */