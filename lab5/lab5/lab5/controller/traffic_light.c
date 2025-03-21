#include <avr/io.h>
#include "traffic_light.h"


void calculatePriority(TrafficLight *self) {
	// Always recalculate, even if bridge is not empty
	int north_time = (self->south_queue == 0) ?
	self->north_queue :
	(self->north_queue / (self->south_queue + 1));
	
	int south_time = (self->north_queue == 0) ?
	self->south_queue :
	(self->south_queue / (self->north_queue + 1));

	// Only switch direction if bridge is empty (safety)
	if (self->cars_on_bridge == 0) {
		if (north_time > south_time) {
			self->direction = 0;
			self->batch_count = (north_time > 0) ? north_time : 1;
			} else {
			self->direction = 1;
			self->batch_count = (south_time > 0) ? south_time : 1;
		}
		self->cars_served = 0;
		} else {
		// Adjust batch count for current direction dynamically
		if (self->direction == 0) {
			self->batch_count = (north_time > 0) ? north_time : 1;
			} else {
			self->batch_count = (south_time > 0) ? south_time : 1;
		}
	}
}

void updateLamps(TrafficLight *self) {
	calculatePriority(self);
	uint8_t new_state = 0;

	if (self->direction == 0 && self->cars_served < self->batch_count) {
		new_state = 0x01 | 0x08; // North green, South red
		} else if (self->direction == 1 && self->cars_served < self->batch_count) {
		new_state = 0x04 | 0x02; // South green, North red
		} else {
		new_state = 0x02 | 0x08; // Both red if batch complete
	}

	self->lamp_state = new_state;
	ASYNC(self->usart, usart_send, self->lamp_state);
	ASYNC(self, updateDisplay, 0);
	
}

void handleSensor(TrafficLight *self, uint8_t sensor) {
	switch (sensor) {
		case 0x01:  // North in
		self->north_queue++;
		break;
		
		case 0x02:  // North out
		if (self->lamp_state & 0x01) {	// North green is on
			self->north_queue--;
			self->cars_on_bridge++;
			ASYNC(self, releaseCar, SEC(5));
		}
		break;
		
		case 0x04:	// South in
		self->south_queue++;
		break;
		
		case 0x08:	// South out
		if (self->lamp_state & 0x04) { // South green is ON
			if (self->south_queue > 0) {
				self->south_queue--;
				self->cars_on_bridge++;
				ASYNC(self, releaseCar, SEC(5));
			}
		}
		break;
	}
	updateLamps(self);
}

void releaseCar(TrafficLight *self, int arg) {
	self->cars_on_bridge--;
	updateLamps(self);
}

void updateDisplay(TrafficLight *self) {
	printAt(self->north_queue, self->pos_north_q);
	printAt(self->south_queue, self->pos_south_q);
	
	if (self->lamp_state & 0x01) {		// North (10) or south (01)
		printAt(10, 2);
		} else {
		printAt(01, 2);
	}
}