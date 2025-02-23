#ifndef _PULSEGEN_
#define _PULSEGEN_

#include "TinyTimber.h"

typedef struct {
	int frequency;
	uint8_t bit;
	uint8_t state;
	Msg pending_msg;
} PulseGen;

void setFrequency();
void toggle();
