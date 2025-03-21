#include "TinyTimber.h"
#include "simulation.h"
#include <pthread.h>

typedef struct {
    Object super;
    char input;
    Simulation *simObject;
} Input_handler;

#define initInput_handler(simRef) \ 
    {initObject(), NULL, simRef}

    
void getUserInput(Input_handler *self);
void procesInput(Input_handler *self, char input);


