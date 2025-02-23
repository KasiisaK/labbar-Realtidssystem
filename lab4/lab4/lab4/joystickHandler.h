#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H

#include <avr/io.h>
#include "TinyTimber.h"
#include "GUI.h"

typedef struct {
    Object super;  // TinyTimber base class
    GUI *gui;      // Reference to the GUI object
} JoystickHandler;

// Macro to initialize a JoystickHandler object
#define initJoystickHandler(guiRef) { initObject(), guiRef }

// Function declarations
void joystickInit();  
void joystickInteruptHandler(JoystickHandler *self, int direction);

#endif
