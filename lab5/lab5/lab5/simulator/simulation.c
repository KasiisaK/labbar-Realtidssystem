#include "simulation.h"


void addNorthCar(Simulation *self) {
    (self->northCarQueue)++;
}

void addSouthCar(Simulation *self) {
    (self->southCarQueue)++;
}

