#ifndef USERINPUT_H
#define USERINPUT_H

#include "simulation.h"

typedef struct {
    char input;
    Simulation *simObject;
} Input;

#define initInput_handler(simRef) \
    {'\0', simRef}  // Initialize with null character

void* getUserInput(void* arg);  // Changed signature
void procesInput(Input *self, char input);

#endif