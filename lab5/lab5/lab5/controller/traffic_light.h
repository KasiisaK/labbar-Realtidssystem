#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "TinyTimber.h"
#include "gui.h"
#include "backend.h"

typedef struct {
	Object super;
	Backend *backend;
	int pos_north_q;
	int pos_south_q;
	int pos_lights;
} TrafficLight;

void handleSensor(TrafficLight *self, uint8_t sensor);
void updateLamps(TrafficLight *self);
void releaseCar(TrafficLight *self, int arg);
void updateDisplay(TrafficLight *self);

#define initTrafficLight(backend_ptr) \
{ initObject(), backend_ptr, 0, 2, 4 }

#endif