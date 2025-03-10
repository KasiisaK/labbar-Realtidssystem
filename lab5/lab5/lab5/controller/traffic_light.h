#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "TinyTimber.h"

typedef struct {
	Object super;
	uint8_t north_queue, south_queue;
	uint8_t lamp_state;
} TrafficLight;

#define initTrafficLight() { initObject(), 0, 0, 0, 0, 0 }
	
#endif