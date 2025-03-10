#include <avr/io.h>
#include "traffic_light.h"

void updateDisplay(TrafficLight *self) {
	printAt(self->north_queue, self->pos_north_q);
	printAt(self->south_queue, self->pos_south_q);
	printAt(self->lamp_state, self->pos_lights);
}

void releaseCar(TrafficLight *self, int arg) {
	if (self->cars_on_bridge == 0) {
		self->direction = !self->direction;
	}
}