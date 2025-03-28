/*
 * backend.h
 *
 * Created: 2025-03-21 13:48:18
 *  Author: askfrs-3
 */ 

#include "TinyTimber.h"
#include "gui.h"
#include "USART.h"

#ifndef BACKEND_H
#define BACKEND_H


typedef struct {
	Object super;
	uint8_t north_queue;
	uint8_t south_queue;
	uint8_t cars_on_bridge;
	uint8_t direction; // 0 = north, 1 = south
	uint8_t lamp_state;
	uint8_t batch_count;
	uint8_t cars_served;
} Backend;

#define backendInit() {initObject(), 0, 0, 0, 0, 0, 0, 0}

void backend_init(Backend *self);
void backend_handleSensor(Backend *self, uint8_t sensor);
uint8_t backend_updateLamps(Backend *self);
void backend_calculatePriority(Backend *self);

#endif
