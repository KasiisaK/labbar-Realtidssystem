#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H

#include <avr/io.h>
#include "TinyTimber.h"
#include "PulseGen.h"

typedef struct {
    Object super;  // TinyTimber base class
    PulseGen *pulsGen;      // Reference to the puls object
    int leftGen;
} JoystickHandler;

// Macro to initialize a JoystickHandler object
#define initJoystickHandler(guiRef) { initObject(), guiRef }

// Function declarations
void joystickInit();  
void joystickInteruptHandler(JoystickHandler *self);

#endif
