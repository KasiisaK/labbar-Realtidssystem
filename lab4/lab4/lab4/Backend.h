#ifndef BACKEND_H
#define BACKEND_H

#include "TinyTimber.h"

typedef struct {
	Object super;
	GUI *gui;
	JoystickHandler *joystickHandler;
	PulseGen *gen1;
	PulseGen *gen2;
	PulseGen *activeGen; //g1 deafult
} BACKEND;

#define initBackend(g1, g2, gui_ptr, joyhandler_ptr) \
	{ initObject(), gui_ptr, joyhandler_ptr, g1, g2, g1 }

//logich stuff
void swithToLeftGen(BACKEND *self);
void swithToRightGen(BACKEND *self);
void adjustFrequency(BACKEND *self, int delta);
void saveRestore(BACKEND *self);


#endif