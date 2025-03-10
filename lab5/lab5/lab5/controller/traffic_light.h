#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "TinyTimber.h"
#include "gui.h"

typedef struct {
	Object super;
	GUI *gui;
	uint8_t north_queue, south_queue;
	uint8_t lamp_state;
	uint8_t direction;					// 0 = north, 1 = south
	uint8_t cars_on_bridge;
	// AVR pos
	uint8_t pos_north_q;
	uint8_t pos_south_q;
	uint8_t pos_lights;
} TrafficLight;

void updateLCD(TrafficLight *self);
void releaseCar(TrafficLight *self, int arg);

#define initTrafficLight() { initObject(), gui, 0, 0, 0, 0, 0 }
	
#endif