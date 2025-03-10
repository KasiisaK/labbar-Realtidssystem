#include "TinyTimber.h"

typedef struct {
    Object super;
    int southCarQueue;
    int northCarQueue;
    int carsOneBridge;
} Simulation;

#define initSimulation() \ 
    {initObject(), 0, 0, 0}

void addNorthCar(Simulation *self);
void addSouthCar(Simulation *self);