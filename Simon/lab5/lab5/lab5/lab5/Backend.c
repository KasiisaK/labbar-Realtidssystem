/*
 * Backend.c
 *
 * Created: 2022-03-10 14:41:30
 *  Author: simeng-0
 */ 

#include "Backend.h"


void start(Backend *self) {
	ASYNC(self->gui, update, 0);
	ASYNC(self->road, updateSignal, 0);
	
}


void receiveN(Backend *self) {
	SYNC(self->road, newNorthBound, 0);
	ASYNC(self->gui, update, 0);
}
void receiveS(Backend *self){
	SYNC(self->road, newSouthBound, 0);
	ASYNC(self->gui, update, 0);
}

void receiveNtoB(Backend *self){
	SYNC(self->road, northToBridge, 0);
	ASYNC(self->gui, update, 0);
	
	AFTER(SEC(5), self->road, exitBridge, 0);
	AFTER(SEC(5), self->gui, update, 0);
}
void receiveStoB(Backend *self){
	SYNC(self->road, southToBridge, 0);
	ASYNC(self->gui, update, 0);
	
	AFTER(SEC(5), self->road, exitBridge, 0);
	AFTER(SEC(5), self->gui, update, 0);
}

void receiveE(Backend *self) {
	
}




//void transmit();
//void transmitNext();