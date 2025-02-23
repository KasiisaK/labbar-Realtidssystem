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
	if (self->frequency == freq) return; // No change needed

	// Cancel any pending toggle
	if (self->pending_msg) {
		BEFORE(self->pending_msg);
		self->pending_msg = NULL;
	}

	self->frequency = freq;

	if (freq <= 0) {
		// Stop generator: set output LOW
		ASYNC(self->writer, setPin(self->bit, 0));
		} else {
		// Start toggling with new frequency
		self->state = 0; // Start LOW
		ASYNC(self->writer, setPin(self->bit, self->state));
		int delay = 500 / freq; // Half-period in ms (50% duty cycle)
		self->pending_msg = AFTER(delay, self, toggle, NULL);
	}
}

// Toggle output and schedule next toggle
void toggle(PulseGen *self) {
	self->state = !self->state;
	ASYNC(self->writer, setPin(self->bit, self->state));

	if (self->frequency > 0) {
		// Schedule next toggle
		int delay = 500 / self->frequency;
		self->pending_msg = AFTER(delay, self, toggle, NULL);
		} else {
		self->pending_msg = NULL; // No further toggles
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