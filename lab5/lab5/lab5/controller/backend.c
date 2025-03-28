#include "backend.h"

void addnorthQ(Backend *self) {
	self->north_queue++;
}

void addsouthQ(Backend *self) {
	self->south_queue++;
}


void mainSimulationLoop(Backend *self) {
	// Calculate light on/off dynamicaly, how many more in north/south side, and deafult to 0 if divison by 0
	int northCarTime = (self->south_queue == 0) ? self->north_queue : (self->north_queue / self->south_queue);
	int southCarTime = (self->north_queue == 0) ? self->south_queue : (self->south_queue / self->north_queue);
	// Start movement in one direction
	SYNC(self, setNorthLightGreen, northCarTime);
	// Wait (5 sec (passing time) + northCarTime) before switching direction
	AFTER(SEC(5) + northCarTime, self, setSouthLightGreen, southCarTime);
	// Wait more (+ southCarTime) time before looping
	AFTER(SEC(5) + northCarTime + southCarTime, self, mainSimulationLoop, NULL);
}

void setNorthLightGreen(Backend *self) {
	self->direction = 0;
	USART_Transmit(0b0000);
	updateDisplay(self);
}

void setSouthLightGreen(Backend *self) {
	self->direction = 1;
	updateDisplay(self);
}

void USART_Transmit(unsigned char data) {
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void updateDisplay(Backend *self) {
	printAt(self->north_queue, 0);
	printAt(self->south_queue, 4);
	printAt(self->cars_on_bridge, 2);
}