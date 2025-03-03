#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H

#include "TinyTimber.h"

typedef struct {
    Object super;
	BACKEND backend;
} JoystickHandler;

#define initJoystickHandler(backendRef) { initObject(), backendRef}

void joystickInit();
void joysticckInteruptHandler(JoystickHandler *self);
void holdDown(JoystickHandler *self);
void holdUp(JoystickHandler *self);

#endif