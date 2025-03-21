#include "backend.h"

void backend_init(Backend *self) {
	self->north_queue = 0;
	self->south_queue = 0;
	self->cars_on_bridge = 0;
	self->direction = 0;
	self->lamp_state = 0;
	self->batch_count = 0;
	self->cars_served = 0;
}

void backend_handleSensor(Backend *self, uint8_t sensor) {
	switch (sensor) {
		case 0x01: // North arrival
		self->north_queue++;
		break;
		case 0x02: // North entry
		if ((self->lamp_state & 0x01) && (self->cars_served < self->batch_count)) {
			self->north_queue--;
			self->cars_on_bridge++;
			self->cars_served++;
		}
		break;
		case 0x04: // South arrival
		self->south_queue++;
		break;
		case 0x08: // South entry
		if ((self->lamp_state & 0x04) && (self->cars_served < self->batch_count)) {
			self->south_queue--;
			self->cars_on_bridge++;
			self->cars_served++;
		}
		break;
	}
}

void backend_calculatePriority(Backend *self) {
	int north_time = (self->south_queue == 0) ?
	self->north_queue :
	(self->north_queue / (self->south_queue + 1));
	
	int south_time = (self->north_queue == 0) ?
	self->south_queue :
	(self->south_queue / (self->north_queue + 1));

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
		if (self->direction == 0) {
			self->batch_count = (north_time > 0) ? north_time : 1;
			} else {
			self->batch_count = (south_time > 0) ? south_time : 1;
		}
	}
}

uint8_t backend_updateLamps(Backend *self) {
	backend_calculatePriority(self);
	uint8_t new_state = 0;

	if (self->direction == 0 && self->cars_served < self->batch_count) {
		new_state = 0x01 | 0x08; // North green, South red
		} else if (self->direction == 1 && self->cars_served < self->batch_count) {
		new_state = 0x04 | 0x02; // South green, North red
		} else {
		new_state = 0x02 | 0x08; // Both red if batch complete
	}

	self->lamp_state = new_state;
	return new_state;
}