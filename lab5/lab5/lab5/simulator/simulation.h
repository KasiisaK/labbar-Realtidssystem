#include "TinyTimber.h"
#include "bridge.h"
#include <stdbool.h>
#include <pthread.h>

typedef struct {
    Object super;
    int southCarQueue;
    int northCarQueue;
    int carsOneBridge;
    bool movingCarsNorth;
    Bridge *bridgeObj;
    pthread_mutex_t *northMtx;
    pthread_mutex_t *southMtx;
    pthread_mutex_t *bridgeMtx;
} Simulation;

#define initSimulation(bridgeRef, noMtx, soMtx, brMtx) \ 
    {initObject(), 0, 0, 0, true, bridgeRef, noMtx, soMtx, brMtx}

// Add and Remove
void switchDirection(Simulation *self);

void addCarBridge(Simulation *self);
void removeCarBridge(Simulation *self);

void addCarNorth(Simulation *self);
void removeNorthCars(Simulation *self);

void addCarSouth(Simulation *self);
void removeSouthCars(Simulation *self);


void moveOverCars(Simulation *self, int forAmountOfTime);
void mainSimulationLoop(Simulation *self);