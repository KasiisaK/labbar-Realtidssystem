/*
 * Road.c
 *
 * Created: 2022-03-08 14:56:45
 *  Author: simeng-0
 */ 

#include "Road.h"



void updateSignal(Road *self) {
	int change = 7;
	Msg m = AFTER(SEC(1), self, updateSignal, 0);   
	
	if(self->wantToChangeDirection == 1 && self->onBridge > 0){
		self->carsSent = 0;
		SYNC(self->lights, redBothDirections, 0);
	}else if (self->wantToChangeDirection == 1 && self->onBridge == 0){
		self->wantToChangeDirection = 0;
		if (self->direction == 'n' && self->southBound > 0){
			self->direction = 's';
			self->carsSent = 1;
			SYNC(self->lights, greenSouthBound, 0);
		}else if(self->direction == 's' && self->northBound > 0){
			self->direction = 'n';
			self->carsSent = 1;
			SYNC(self->lights, greenNorthBound, 0);
		}
	}else if(self->northBound == 0 && self->southBound == 0 && self->onBridge == 0) {
		self->carsSent = 0;
		self->direction = 'p';
		SYNC(self->lights, redBothDirections, 0);
		ABORT(m);
	}else if(self->direction == 'p' && (self->northBound > 0 || self->southBound > 0) && self->onBridge == 0) {
		if(self->northBound > 0 && self->southBound > 0) {
			self->carsSent++;
			self->direction = 'n';
			SYNC(self->lights, greenNorthBound, 0);
		}else if(self->northBound > 0 && self->southBound == 0) {
			self->carsSent++;
			self->direction = 'n';
			SYNC(self->lights, greenNorthBound, 0);
		}else if(self->northBound == 0 && self->southBound > 0) {
			self->carsSent++;
			self->direction = 's';
			SYNC(self->lights, greenSouthBound, 0);			
		}
	}else if(self->direction == 's') {
		if(self->northBound == 0 && self->southBound > 0) {
			self->carsSent++;
			self->direction = 's';
			SYNC(self->lights, greenSouthBound, 0);
		}else if(self->southBound > 0 && self->northBound > 0 && self->carsSent < change){
			self->carsSent++;
			self->direction = 's';
			SYNC(self->lights, greenSouthBound, 0);
		}else if(self->northBound > 0 && (self->carsSent >= change || self->southBound == 0)){ // 
			self->wantToChangeDirection = 1;
		}
	}else if(self->direction == 'n'){
		if(self->southBound == 0 && self->northBound > 0) {
			self->carsSent++;
			self->direction = 'n';
			SYNC(self->lights, greenNorthBound, 0);
		}else if(self->northBound > 0 && self->southBound > 0 && self->carsSent < change){
			self->carsSent++;
			self->direction = 'n';
			SYNC(self->lights, greenNorthBound, 0);
		}else if(self->southBound > 0 && (self->carsSent >= change || self->northBound == 0)){ // 
			self->wantToChangeDirection = 1;
		}
	}
}


void cycle(Road *self){	//working name
	int sent = 0;
	int changed = 0;
	
	
	//tries to continue sending cars in the same direction
	if(self->direction == 's' && self->southBound > 0){
		self->carsLeftUntilChange--;
		ASYNC(self->lights, greenSouthBound, 0);
		sent = 1;
	}else if(self->direction == 'n' && self->northBound > 0){
		self->carsLeftUntilChange--;
		ASYNC(self->lights, greenNorthBound, 0);
		sent = 1;
	}
	
	//if no car has been sent (current traffic direction is empty), it'll change direction and send send a car from there
	if(sent == 0){
		if (self->northBound > self->southBound){
			self->direction = 'n';
			ASYNC(self->lights, greenNorthBound, 0);
		}else{
			self->direction = 's';
			ASYNC(self->lights, greenSouthBound, 0);
		}
		self->carsLeftUntilChange = 15;
	}
	
	//changes direction if too many cars from one direction has passed
	if(self->carsLeftUntilChange == 0){
		if(self->direction == 'n' && self->southBound > 0){
			self->direction = 's';
			changed = 1;
		}else if(self->direction == 's' && self->northBound > 0){
			self->direction = 'n';
			changed = 1;
		}
		self->carsLeftUntilChange = 15;
	}
	
	//it'll call itself again as long as there are cars left. If the direction was changed it'll wait five seconds, otherwise one. 
	if(self->northBound > 0 || self->southBound > 0){
		if(changed == 1){
			ASYNC(self->lights, redNorthBound, 0);
			ASYNC(self->lights, redSouthBound, 0);
			AFTER(SEC(5), self, cycle, 0);
		}else{
			AFTER(SEC(1), self, cycle, 0);
		}
	}else{
		self->carsLeftUntilChange = 15;
	}
}


void driveNorth(Road *self) {
	self->paused = 0;
	if(self->northBound > 0 && self->carsSent < 7) {
		self->carsSent++;
		self->direction = 'n';
		SYNC(self->lights, greenNorthBound, 0);
		AFTER(SEC(1), self, driveNorth, 0);
	}else if(self->southBound == 0 && self->northBound > 0) {
		self->direction = 'n';
		SYNC(self->lights, greenNorthBound, 0);
		AFTER(SEC(1), self, driveNorth, 0);
	}else{
		self->carsSent = 0; //reset
		ASYNC(self, redBoth, 0);
	}
}

void driveSouth(Road *self) {
	self->paused = 0;
	if(self->southBound > 0 && self->carsSent < 7) {
		self->carsSent++;
		self->direction = 's';
		SYNC(self->lights, greenSouthBound, 0);
		AFTER(SEC(1), self, driveSouth, 0);
	} else if(self->northBound == 0 && self->southBound > 0) {
		self->direction = 's';
		SYNC(self->lights, greenSouthBound, 0);
		AFTER(SEC(1), self, driveSouth, 0);
	} else{
		self->carsSent = 0; //reset
		ASYNC(self, redBoth, 0);
	}
}

void redBoth(Road *self) {
	SYNC(self->lights, redBothDirections, 0);
	if(self->northBound == 0 && self->southBound == 0) {
		self->paused = 1;
		return;
	}else {
		if(self->direction == 'n' && self->southBound > 0) { // last direction was N, check if there are cars that want to go south
			AFTER(SEC(5), self, driveSouth, 0);
		}else if(self->direction == 's' && self->northBound > 0){
			AFTER(SEC(5), self, driveNorth, 0);
		}
	}
}

void newNorthBound(Road *self){
	/*if(!(self->onBridge > 0  && self->direction == 'n' && self->paused == 0)){
		if(self->northBound == 0 && self->southBound == 0  && !(self->onBridge > 0 && self->direction == 's')) {
			//ASYNC(self, cycle, 0);
			ASYNC(self, driveNorth, 0);
		}
	}*/
	
	/*
	if(self->direction == 'p') { //gör samma på newSouthBound
		self->northBound++;
		//KANSKE (tror det ska vara där): self->direction = 'n' // kanske blir konstigt om man inte har detta när man lägger till flera bilar mycket snabbt
		ASYNC(self, updateSignal, 0)
	}else {
		self->northBound++;
	]
	
	*/
	if(self->direction == 'p'){
		ASYNC(self, updateSignal, 0);
	}
	self->northBound++;
}
void newSouthBound(Road *self){
	/*if(!(self->onBridge > 0  && self->direction == 's' && self->paused == 0)){
		
		if(self->northBound == 0 && self->southBound == 0  && !(self->onBridge > 0 && self->direction == 'n')) {
			//ASYNC(self, cycle, 0);
			ASYNC(self, driveSouth, 0);
		}
	}*/
	if(self->direction == 'p'){
		ASYNC(self, updateSignal, 0);
	}
	self->southBound++;
}
int getNorthBound(Road *self){
	return self->northBound;
}
int getSouthBound(Road *self){
	return self->southBound;
}
void northToBridge(Road *self){
	self->northBound--;
	self->onBridge++;
	//AFTER(SEC(5), self, exitBridge, 0);
}
void southToBridge(Road *self){
	self->southBound--;
	self->onBridge++;
	//AFTER(SEC(5), self, exitBridge, 0);
}
int getOnBridge(Road* self){
	return self->onBridge;
}
void exitBridge(Road *self){
	self->onBridge--;
	
	/*if(self->onBridge == 0){
		if(self->direction == 'n' && self->southBound > 0){
			ASYNC(self, driveSouth, 0);
		}else if(self->direction == 's' && self->northBound > 0){
			ASYNC(self, driveNorth, 0);
		}
	}*/
}