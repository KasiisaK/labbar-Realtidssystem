#ifndef _PULSEGEN_
#define _PULSEGEN_

#include "TinyTimber.h"

typedef struct {
	Object super;		// Inherit TinyTimber
	uint8_t bit;		// Port E
	uint8_t state;		// HIGH/LOW output
	Msg pending_msg;	// Pending toggle msg
	int frequency;		// Current freq
} PulseGen;

void setFrequency(PulseGen *self, int freq);
void toggle(PulseGen *self);

#endif