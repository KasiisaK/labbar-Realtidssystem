#include "TinyTimber.h"
#include "bridge.h"
#include <stdbool.h>

typedef struct {
    Object super;
    int southCarQueue;
    int northCarQueue;
    int carsOneBridge;
    bool movingCarsNorth;
    Bridge *bridgeObj;
} Simulation;

#define initSimulation(bridgeRef) \ 
    {initObject(), 0, 0, 0, true, bridgeRef}

void addNorthCar(Simulation *self);
void addSouthCar(Simulation *self);
void mainSimulationLoop(Simulation *self);