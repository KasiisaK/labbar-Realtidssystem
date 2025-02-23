/*
 * lab4.c
 *
 * Created: 22/02/2025 17:10:33
 * Author : Frossel
 */ 

#include <avr/io.h>
#include "PulseGen.h"
#include "PortWrite.h"


void setFrequency(PulseGen *self, int freq) {
    if (freq == self->frequency) return;
    
    // Cancel pending events
    if (self->pending_msg) {
        ABORT(self->pending_msg);
    }
    
    self->frequency = freq;
    
    if (freq > 0) {
        // Start new toggle cycle
        int period = 1000 / freq;  // Full period in ms
        self->state = 1;
        ASYNC(self->writer, setPin, self->bit | (self->state << self->bit));
        self->pending_msg = AFTER(period/2, self, toggle, 0);
    } else {
        // Set output low
        ASYNC(self->writer, setPin, self->bit | 0);
    }
}

// Toggle output and schedule next toggle
void toggle(PulseGen *self) {
    self->state = !self->state;
    ASYNC(self->writer, setPin, self->bit | (self->state << self->bit));
    
    if (self->frequency > 0) {
        int period = 1000 / self->frequency;
        self->pending_msg = AFTER(period/2, self, toggle, 0);
    }
}

// Saves the freq
void save(PulseGen *self) {
	self->saved_freq = self->frequency;
}

// Restores freq to last saved
void restore(PulseGen *self) {
	ASYNC(self, setFrequency(self->saved_freq));
}

void increaseFreq(PulseGen *self){
	self->frequency++;
}

void decreaseFreq(PulseGen *self)[
	self->frequency--;
	if (self->frequency < 0){
		self->frequency = 0;
	}
]