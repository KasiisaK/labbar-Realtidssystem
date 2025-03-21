#include "simulation.h"
#include <stdbool.h>

void switchDirection(Simulation *self) {
    self->movingCarsNorth = !self->movingCarsNorth;
}

// Bridge
void addCarBridge(Simulation *self) {
    pthread_mutex_lock(&(self->bridgeMtx));
    (self->carsOneBridge)++;
    pthread_mutex_unlock(&(self->bridgeMtx));
}
void removeCarBridge(Simulation *self) {
    if (self->carsOneBridge > 0) {
        pthread_mutex_lock(&(self->bridgeMtx));
        (self->carsOneBridge)--;
        pthread_mutex_unlock(&(self->bridgeMtx));
    }
}

// North
void addCarNorth(Simulation *self) {
    pthread_mutex_lock(&(self->northMtx));
    (self->northCarQueue)++;
    pthread_mutex_unlock(&(self->northMtx));
}
void removeNorthCars(Simulation *self) {
    if (self->northCarQueue > 0) {
        pthread_mutex_lock(&(self->northMtx));
        (self->northCarQueue)--;
        pthread_mutex_unlock(&(self->northMtx));
    }
}

// South
void addCarSouth(Simulation *self) {
    pthread_mutex_lock(&(self->southMtx));
    (self->southCarQueue)++;
    pthread_mutex_unlock(&(self->southMtx));
}
void removeSouthCars(Simulation *self) {
    if (self->southCarQueue > 0) {
        pthread_mutex_lock(&(self->southMtx));
        (self->southCarQueue)--;
        pthread_mutex_unlock(&(self->southMtx));
    }
}

void mainSimulationLoop(Simulation *self) {
    
    //kanske get metod och mutex?
    if (SYNC(self->bridgeObj, getNorthLightStatus, NULL)) {
        SYNC(self, removeNorthCars, NULL);
    }
    if (SYNC(self->bridgeObj, getSouthLightStatus, NULL)) {
        SYNC(self, removeSouthCars, NULL);
    }
    SYNC(self, addCarBridge, NULL);

    // Remove car from bridge after 5 sec 
    AFTER(SEC(5), self, removeCarBridge, NULL);

    // A car passed every second so call loop every second
    AFTER(SEC(1), self, mainSimulationLoop, NULL);
}

