#ifndef JOYSTICKHANDLER_H
#define JOYSTICKHANDLER_H

#include <avr/io.h>


typedef struct {
    
} JoystickHandler;

#define initJoystickHandler() { initObject(), }

void joystickInit();
void joystickInteruptHandler(JoystickHandler *self);

#endif