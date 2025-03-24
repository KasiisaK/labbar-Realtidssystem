#ifndef _MAIN_
#define _MAIN_

#include "GUI.h"
#include "InterruptHandler.h"
#include "Lights.h"
#include "Road.h"
#include "TinyTimber.h"
#include <avr/io.h>

Lights lights;
Road road;
GUI gui;
InterruptHandler handler;
Backend backend;


void init(void);

#endif