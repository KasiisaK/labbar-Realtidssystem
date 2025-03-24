/*
 * Lights.c
 *
 * Created: 2022-03-08 14:57:15
 *  Author: simeng-0
 */ 

#include "Lights.h"



void greenSouthBound(Lights *self){
	self->southStatus = 1;
	UDR0 = 0b0100 | (self->northStatus == 1 ? 0b0001 : 0b0010);
}
	
void redSouthBound(Lights *self){
	self->southStatus = 0;
	UDR0 = 0b1000 | (self->northStatus == 1 ? 0b0001 : 0b0010);
}

void greenNorthBound(Lights *self){
	self->northStatus = 1;
	UDR0 = 0b0001 | (self->southStatus == 1 ? 0b0100 : 0b1000);
}

void redNorthBound(Lights *self){
	self->northStatus = 0;
	UDR0 = 0b0010 | (self->southStatus == 1 ? 0b0100 : 0b1000);
}

void redBothDirections(Lights *self) {
	self->northStatus = 0;
	self->southStatus = 0;
	UDR0 = 0b1010;
}





