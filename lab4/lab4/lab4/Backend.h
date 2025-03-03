#ifndef BACKEND_H
#define BACKEND_H

#include "TinyTimber.h"

typedef struct {
	Object super;
	GUI *gui;
	JoystickHandler joystickhandr;
	PulseGen *gen1;
	PulseGen *gen2;
	PulseGen *activeGen; //g1 deafult
} BACKEND;

#define initBackend(g1, g2, gui, joyhandler) { initObject(), gui, joyhandler, g1, g2, g1}

//logich stuff
void swithToLeftGen(GUI *self);
void swithToRightGen(GUI *self);
void adjustFrequency(GUI *self, int delta);
void saveRestore(GUI *self);

#endif