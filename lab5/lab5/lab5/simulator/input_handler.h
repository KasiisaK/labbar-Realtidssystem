#include "simulation.h"
#include <pthread.h>

typedef struct {
    char input;
    Simulation *simObject;
} Input_handler;

#define initInput_handler(simRef) \ 
    {NULL, simRef}

    
void getUserInput(Input_handler *self);
void procesInput(Input_handler *self, char input);


