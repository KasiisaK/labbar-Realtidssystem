#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H

#include "TinyTimber.h"
#include "gui.h"

typedef struct {
    Object super;
    GUI *gui;
} JoystickHandler;

#define initJoystickHandler(guiRef) { initObject(), guiRef }

void joystickInit();
void interruptPinB(JoystickHandler *self);
void interruptPinE(JoystickHandler *self);

#endif