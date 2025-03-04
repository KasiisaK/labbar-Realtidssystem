#include "Backend.h"


void swithToLeftGen(Backend *self) {
	self->activeGen = self->gen2;
	SYNC(self->gui, setActive, true);
	SYNC(self->gen1, setStatus, 0);
	SYNC(self->gen2, setStatus, 1);
	ASYNC(self->gui, updateDisplay, 10);
}

void swithToRightGen(Backend *self) {
	self->activeGen = self->gen1;
	SYNC(self->gui, setActive, false);
	SYNC(self->gen1, setStatus, 1);
	SYNC(self->gen2, setStatus, 0);
	ASYNC(self->gui, updateDisplay, 20);
}

void adjustFrequency(Backend *self, int delta) {
	// Get right target gen
	int newFreq = SYNC(self->activeGen, getFrequency, 0) + delta;
	if (newFreq < 0) newFreq = 0;
	// Update everything
	SYNC(self->activeGen, setFrequency, newFreq);
	ASYNC(self->gui, updateDisplay, 0);
}

void saveRestore(Backend *self) {
	if (SYNC(self->activeGen, getFrequency, 0) == 0) {
		SYNC(self->activeGen, restore, 0);
		} else {
		SYNC(self->activeGen, save, 0);
		SYNC(self->activeGen, setFrequency, 0);
	}
	ASYNC(self->gui, updateDisplay, 0);
}

void startProgram(Backend *self) {
	SYNC(self->gen1, genFreq, 0);
	SYNC(self->gen2, genFreq, 0);
}
