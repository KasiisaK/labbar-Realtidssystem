#include "TinyTimber.h"
#include "simulation.h"

typedef struct {
    Object super;
    char input;
} Input_handler;

#define initInput_handler() \ 
    {initObject(), NULL}

void getUserInput(Input_handler *self);
void procesInput(Input_handler *self, char input);


