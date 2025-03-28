#include "backend.h"
#include <util/delay.h>


#define NORTH_GREEN 0b0001
#define NORTH_RED	0b0010
#define SOUTH_GREEN 0b0100
#define SOUTH_RED   0b1000

void addnorthQ(Backend *self) {
	self->north_queue++;
}

void addsouthQ(Backend *self) {
	self->south_queue++;
}

void addBrdigeQ(Backend *self) {
	self->cars_on_bridge++;
}


void mainSimulation(Backend *self) {
	// Calculate light on/off dynamicaly, how many more in north/south side, and deafult to 0 if divison by 0
	int northCarTime = (self->south_queue == 0) ? self->north_queue : (self->north_queue / self->south_queue);
	int southCarTime = (self->north_queue == 0) ? self->south_queue : (self->south_queue / self->north_queue);
	// Start movement in one direction
	SYNC(self, setNorthLightGreen, northCarTime);
	// Wait (5 sec (passing time) + northCarTime) before switching direction
	AFTER(SEC(5), self, setSouthLightGreen, southCarTime);
	// Wait more (+ southCarTime) time before looping
	int timePass = (5*1000) + (southCarTime*1000);
	while(timePass > 0) {
		timePass--;
	}
}

void setNorthLightGreen(Backend *self) {
	self->direction = 0;
	SYNC(self, USART_Transmit, SOUTH_RED);
	LightIndicator('s', 0);
	updateDisplay(self);
	AFTER(SEC(5), self, USART_Transmit, NORTH_GREEN);	
	LightIndicator('n', 1);
	updateDisplay(self);
}

void setSouthLightGreen(Backend *self) {
	self->direction = 1;
	SYNC(self, USART_Transmit, NORTH_RED);
	LightIndicator('n', 0);
	updateDisplay(self);
	AFTER(SEC(5), self, USART_Transmit, SOUTH_GREEN);
	LightIndicator('s', 1);
	updateDisplay(self);
}

void USART_Transmit(Backend *self, unsigned char data) {
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) );
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

void updateDisplay(Backend *self) {
	printAt(self->north_queue, 0);
	printAt(self->south_queue, 4);
	printAt(self->cars_on_bridge, 2);
}