#ifndef BACKEND_H
#define BACKEND_H

#include "TinyTimber.h"
#include "GUI.h"
#include "PulseGen.h"


typedef struct {
	Object super;
	GUI *gui;
	PulseGen *gen1;
	PulseGen *gen2;
	PulseGen *activeGen; //g1 default
} Backend;

#define initBackend(g1, g2, gui_ptr) \
	{ initObject(), gui_ptr, g1, g2, g1 }

//logic stuff
void swithToLeftGen(Backend *self);
void swithToRightGen(Backend *self);
void adjustFrequency(Backend *self, int delta);
void saveRestore(Backend *self);
void startProgram(Backend *self);


#endif