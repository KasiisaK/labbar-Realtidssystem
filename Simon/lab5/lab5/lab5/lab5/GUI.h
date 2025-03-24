/*
 * GUI.h
 *
 * Created: 2022-03-08 14:58:31
 *  Author: simeng-0
 */ 


#ifndef GUI_H_
#define GUI_H_

#include <avr/io.h>
#include "Road.h"
#include "TinyTimber.h"


#define initGUI(r) { initObject(), r }

typedef struct {
	Object super;
	Road *road;
} GUI;

void update(GUI *self);


#endif /* GUI_H_ */