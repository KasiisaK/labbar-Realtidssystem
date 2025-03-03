#ifndef _PULSEGEN_
#define _PULSEGEN_

#include <stdbool.h>
#include "TinyTimber.h"
#include "PortWrite.h"

typedef struct {
	Object super;		// Inherit TinyTimber
	uint8_t bit;		// Port E (4 or 6)
	uint8_t state;		// HIGH/LOW output
	Msg pending_msg;	// Pending toggle msg
	int frequency;		// Current freq
	int saved_freq;		// Last saved freq
	PortWrite *write;
	bool genStatus;
} PulseGen;

#define initPulseGen(bit, writer, status) \
	{ initObject(), bit, 0, 0, 0, 0, writer, status }

void freqInit(PulseGen *self);
void setFrequency(PulseGen *self, int freq);
void toggle(PulseGen *self);
void save(PulseGen *self);
void restore(PulseGen *self);
void setStatus(PulseGen *self, bool status);
int getFrequency(PulseGen *self);
int genFreq(PulseGen *self);

#endif