#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H

#include "TinyTimber.h"
#include "Backend.h"
#include <avr/io.h>


typedef struct {
    Object super;
	Backend *BE;
} JoystickHandler;

#define initJoystickHandler(backendRef) { initObject(), backendRef}

void joystickInit();
void joystickInteruptHandler(JoystickHandler *self);

#endif