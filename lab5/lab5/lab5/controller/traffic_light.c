#include <avr/io.h>
#include "traffic_light.h"

void updateDisplay(TrafficLight *self) {
	printAt(self->north_queue, self->pos_north_q);
	printAt(self->south_queue, self->pos_south_q);
	printAt(self->lamp_state, self->pos_lights);
	
	if (self->direction == 0) {		// North (10) or south (01)
		printAt(10, 2);					
	} else {
		printAt(01, 2);
	}
}

void updateLamps(TrafficLight *self, uint8_t sensor) {
	uint8_t new_state = 0;
	switch (sensor) {
		case ???:  //north in
			self->north_queue++;
			break;
		case ???:  // north out
			if (self->lamp_state & 0x01) {
				self->north_queue--;
				self->cars_on_bridge++;
				ASYNC(self, releaseCar, 0, SEC(5));
			}
			break;
		case ???;
			break;
		case ???;
			break;
		
	}
	updateLamps(self);
}

void handleSensor(TrafficLight *self, uint8_t sensor) {
	
}

void releaseCar(TrafficLight *self, int arg) {
	self->cars_on_bridge--;
	if (self->cars_on_bridge == 0) {
		self->direction = !self->direction;
	}
	updateLamps(self);
}