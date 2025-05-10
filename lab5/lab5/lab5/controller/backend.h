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

void addnorthQ(Backend *self);
void addsouthQ(Backend *self);
void addBrdigeQ(Backend *self);

void setNorthLightGreen(Backend *self);
void setSouthLightGreen(Backend *self);

void mainSimulation(Backend *self);

void USART_Transmit(Backend *self, unsigned char data);
void updateDisplay(Backend *self);

#endif
