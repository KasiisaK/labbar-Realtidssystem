/*
 * lab4.c
 *
 * Created: 22/02/2025 17:10:33
 * Author : Frossel
 */ 

#include <avr/io.h>
#include "PulseGen.h"
#include <util/delay.h>

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

void genFreq(PulseGen *self) {
	
	
	if (self->frequency == 0) {
		SYNC(self->write, turnOffPin, self->bit);
		AFTER(SEC(1), self, genFreq, 0);
	} else {		
		int freq = (int)(500 / self->frequency);
		AFTER(MSEC(freq), self, genFreq, 0);
		SYNC(self->write, togglePin, self->bit);
	}
	
	
	
	/*
	while (1) {		
		if (self->frequency == 0) {
			SYNC(self->write, turnOffPin, self->bit);
		} else {
			int freq = (int)(500 / 1);
			SYNC(self->write, togglePin, self->bit);
			_delay_ms(freq);
			
		}
	}
	*/
}