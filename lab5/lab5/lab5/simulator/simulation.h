#ifndef SIMULATION_H
#define SIMULATION_H

#include "bridge.h"
#include "PCReader.h"
#include <stdbool.h>

typedef struct {
    int southCarQueue;
    int northCarQueue;
    int carsGoingSouth;
	int carsGoingNorth;
    Bridge *bridgeObj;
    pthread_mutex_t northMtx;
    pthread_mutex_t southMtx;
    pthread_mutex_t bridgeMtx;
	unsigned char output;
    Reader *readerRef;
    int port_fd; // For wirting to AVR
} Simulation;

#define initSimulation(bridgeRef, redRef, portRef) \
    {0, 0, 0, 0, bridgeRef, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, PTHREAD_MUTEX_INITIALIZER, 0b0000, redRef, portRef}

void printState(Simulation *self);

// Data get for PCComunication
unsigned char getData(Simulation *self);

// Add and Remove
void addNorthCarBridge(Simulation *self);
void addSouthCarBridge(Simulation *self);

void addCarNorth(Simulation *self);
void removeNorthCars(Simulation *self);

void addCarSouth(Simulation *self);
void removeSouthCars(Simulation *self);


void* procesUSARTData(void *arg);

void* removeNorthCarBridge(void* arg);
void* removeSouthCarBridge(void* arg);
void* mainSimulationLoop(void* arg);

#endif