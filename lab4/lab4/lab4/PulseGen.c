/*
 * lab4.c
 *
 * Created: 22/02/2025 17:10:33
 * Author : Frossel
 */ 

#include <avr/io.h>
#include "PulseGen.h"
#include "PortWrite.h"
#include "TinyTimber.h"


void setFrequency(PulseGen *self, int freq) {
	self->frequency = freq;
}

// Saves the freq
void save(PulseGen *self) {
	self->saved_freq = self->frequency;
}

// Restores freq to last saved
void restore(PulseGen *self) {
	self->frequency = self->saved_freq;
}

int getFrequency(PulseGen *self) {
	return self->frequency;
}

void setStatus(PulseGen *self, bool status) {
	self->genStatus = status;
}

int genFreq(PulseGen *self) {
	if (self->genStatus) {
		
	}
}