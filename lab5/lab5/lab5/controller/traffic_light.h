#ifndef TRAFFICLIGHT_H
#define TRAFFICLIGHT_H

#include "TinyTimber.h"
#include "gui.h"
#include "USART.h"

typedef struct {
	Object super;
	GUI *gui;
	USART *usart;
	uint8_t north_queue, south_queue;
	uint8_t lamp_state;
	uint8_t direction;					// 0 = north, 1 = south
	uint8_t cars_on_bridge;
	uint8_t batch_count;     // Max cars allowed in current batch
	uint8_t cars_served;     // Cars passed in current batch
	// AVR pos
	uint8_t pos_north_q;
	uint8_t pos_south_q;
	uint8_t pos_lights;
} TrafficLight;

void handleSensor(TrafficLight *self, uint8_t sensor);
void updateLamps(TrafficLight *self);
void releaseCar(TrafficLight *self, int arg);
void updateDisplay(TrafficLight *self);
void calculatePriority(TrafficLight *self);


#define initTrafficLight(gui_ptr, usart_ptr) \
	{ initObject(), gui_ptr, usart_ptr, 0, 0, 0, 0, 0, 0, 2, 4, 0, 0 }
	
#endif