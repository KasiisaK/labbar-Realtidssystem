#include "TinyTimber.h"
#include "Backend.h"
#include "GUI.h"


void swithToLeftGen(BACKEND *self) {
	self->activeGen = self->gen1;
	SYNC(self->gen1, setStatus, 1);
	SYNC(self->gen2, setStatus, 0);
	ASYNC(self, updateDisplay, 0);
}

void swithToRightGen(BACKEND *self) {
	self->activeGen = self->gen2;
	SYNC(self->gen1, setStatus, 0);
	SYNC(self->gen2, setStatus, 1);
	ASYNC(self, updateDisplay, 0);
}

void adjustFrequency(BACKEND *self, int delta) {
	// Get right target gen
	int newFreq = SYNC(self->activeGen, getFrequency, 0) + delta;
	if (newFreq < 0) newFreq = 0;
	// Update everything
	SYNC(self->activeGen, setFrequency, newFreq);
	ASYNC(self, updateDisplay, 0);
}

void saveRestore(BACKEND *self) {
	if (SYNC(self->activeGen, getFrequency, 0) == 0) {
		SYNC(self->activeGen, restore, 0);
		} else {
		SYNC(self->activeGen, save, 0);
		SYNC(self->activeGen, setFrequency, 0);
	}
	ASYNC(self, updateDisplay, 0);
}

