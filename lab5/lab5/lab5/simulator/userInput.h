#include "simulation.h"

typedef struct {
    char input;
    Simulation *simObject;
} Input;

#define initInput_handler(simRef) \ 
    {NULL, simRef}

    
void getUserInput(Input *self);
void procesInput(Input *self, char input);


