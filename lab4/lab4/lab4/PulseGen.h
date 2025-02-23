#ifndef _PULSEGEN_
#define _PULSEGEN_

#include "TinyTimber.h"

typedef struct {
	Object super;
	uint8_t bit;
	uint8_t state;
	Msg pending_msg;
	int frequency;
} PulseGen;

void setFrequency();
void toggle();
