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

// Toggle output and schedule next toggle
void toggle(PulseGen *self) {
    self->state = !self->state;
    ASYNC(self->write, setPin, self->bit | (self->state << self->bit));
    
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
	self->frequency = self->saved_freq;
}

int getFrequency(PulseGen *self) {
	return self->frequency;
}

