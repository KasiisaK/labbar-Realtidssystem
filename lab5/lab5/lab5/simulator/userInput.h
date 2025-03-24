#ifndef USERINPUT_H
#define USERINPUT_H

#include "simulation.h"

typedef struct {
    char input;
    Simulation *simObject;
} Input;

#define initInput_handler(simRef) \
    {'0', simRef}

    
void getUserInput(Input *self);
void procesInput(Input *self, char input);

#endif

