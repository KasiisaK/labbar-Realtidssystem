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

void moveOverCars(Simulation *self, int forAmountOfTime) {
    // Check if time is done
    if (forAmountOfTime <= 0) {
        // Swith for next light
        SYNC(self, switchDirection, NULL);
        SYNC(self->bridgeObj, switchLightState, NULL);
        return;
    }

    // Cars going north
    if (self->movingCarsNorth) {
        SYNC(self, removeNorthCars, NULL);
    
    // Cars going south
    } else {
        SYNC(self, removeSouthCars, NULL);
    }
    // Add car on bridge after removing south/north
    ASYNC(self, addCarBridge, NULL);

    // Loop every second and decreas the time 
    AFTER(SEC(1), self, moveOverCars, forAmountOfTime - 1);

    // Remove car after 5 second (time to pass)
    AFTER(SEC(5), self, removeCarBridge, NULL);
}

void mainSimulationLoop(Simulation *self) {
    // Calculate light on/off dynamicaly, how many more in north/south side, and deafult to 0 if divison by 0
    int northCarTime = (self->southCarQueue == 0) ? self->northCarQueue : (self->northCarQueue / self->southCarQueue);
    int southCarTime= (self->northCarQueue == 0) ? self->southCarQueue : (self->southCarQueue / self->northCarQueue);


    // Start movement in one direction
    SYNC(self, moveOverCars, northCarTime);

    // Wait (5 sec (passing time) + northCarTime) before switching direction
    AFTER(SEC(5) + northCarTime, self, moveOverCars, southCarTime);

    // Wait more (+ southCarTime) time before looping
    AFTER(SEC(5) + northCarTime + southCarTime, self, mainSimulationLoop, NULL);
}

