#include "bridge.h"
#include "USART.h"
#include <stdbool.h>
#include <pthread.h>

typedef struct {
    int southCarQueue;
    int northCarQueue;
    int carsGoingSouth;
	int carsGoingNorth;
    bool movingCarsNorth;
	bool movingCarsSouth;
    Bridge *bridgeObj;
    pthread_mutex_t *northMtx;
    pthread_mutex_t *southMtx;
    pthread_mutex_t *bridgeMtx;
	unsigned char output;
	USART *usartRef;
} Simulation;

#define initSimulation(bridgeRef, noMtx, soMtx, brMtx) \ 
    {0, 0, 0, 0, true, false, bridgeRef, noMtx, soMtx, brMtx, 0b0000, NULL} // Temp NULL

// Data get for USART
unsigned char getData(Simulation *self);

// Add and Remove
void addNorthCarBridge(Simulation *self);
void removeNorthCarBridge(Simulation *self);
void addSouthCarBridge(Simulation *self);
void removeSouthCarBridge(Simulation *self);


void addCarNorth(Simulation *self);
void removeNorthCars(Simulation *self);

void addCarSouth(Simulation *self);
void removeSouthCars(Simulation *self);

void procesUSARTData(Simulation *self);
void mainSimulationLoop(Simulation *self);