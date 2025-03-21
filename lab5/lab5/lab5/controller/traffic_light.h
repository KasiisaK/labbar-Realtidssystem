#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "TinyTimber.h"
#include "gui.h"
#include "backend.h"

typedef struct {
	Object super;
	GUI *gui;
	Backend *backend;
	uint8_t pos_north_q;
	uint8_t pos_south_q;
	uint8_t pos_lights;
} TrafficLight;

void handleSensor(TrafficLight *self, uint8_t sensor);
void updateLamps(TrafficLight *self);
void releaseCar(TrafficLight *self, int arg);
void updateDisplay(TrafficLight *self);

#define initTrafficLight(gui_ptr, backend_ptr) \
{ initObject(), gui_ptr, backend_ptr, 0, 2, 4 }

#endif