/*
 * InterruptHandler.c
 *
 * Created: 2022-03-08 14:53:11
 *  Author: simeng-0
 */ 
#include "InterruptHandler.h"



void receiveInterrupt(InterruptHandler *self){
	
	unsigned int input = UDR0;
	if(input & 0b0001){
		ASYNC(self->backend, receiveN, 0);
	}else if(input & 0b0100) {
		ASYNC(self->backend, receiveS, 0);
	}else if(input & 0b0010){
		ASYNC(self->backend, receiveNtoB, 0);
	}else if(input & 0b1000){
		ASYNC(self->backend, receiveStoB, 0);
	}

}

void transmitInterrupt(InterruptHandler *self){
	char yeet = UDR0;
}

void regEmptyInterrupt(InterruptHandler *self) {

}







