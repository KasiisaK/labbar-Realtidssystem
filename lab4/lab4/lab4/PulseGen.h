#ifndef _PULSEGEN_
#define _PULSEGEN_

#include <stdbool.h>
#include "TinyTimber.h"
#include "PortWrite.h"

typedef struct {
	Object super;		// Inherit TinyTimber
	uint8_t bit;		// Port E (4 or 6)
	uint8_t state;		// HIGH/LOW output
	int frequency;		// Current freq
	int saved_freq;		// Last saved freq
	PortWrite *write;
} PulseGen;

#define initPulseGen(bit, writer ) \
	{ initObject(), bit, 0, 0, 0, writer }

void setFrequency(PulseGen *self, int freq);
void toggle(PulseGen *self);
void save(PulseGen *self);
void restore(PulseGen *self);
int getFrequency(PulseGen *self);
void genFreq(PulseGen *self);

#endif