#include <avr/io.h>
#include "traffic_light.h"


void updateLamps(TrafficLight *self) {
	uint8_t lamp_state = backend_updateLamps(self->backend);
	ASYNC(self, updateDisplay, 0);
}

void handleSensor(TrafficLight *self, uint8_t sensor) {
	backend_handleSensor(self->backend, sensor);
	updateLamps(self);
}

void releaseCar(TrafficLight *self, int arg) {
	self->backend->cars_on_bridge--;
	updateLamps(self);
}

void updateDisplay(TrafficLight *self) {
    printAt(self->backend->north_queue, self->pos_north_q);
    printAt(self->backend->south_queue, self->pos_south_q);
}