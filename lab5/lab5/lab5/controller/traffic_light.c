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

