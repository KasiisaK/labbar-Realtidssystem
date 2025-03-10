#include "simulation.h"
#include <stdbool.h>

void switchDirection(Simulation *self) {
    self->movingCarsNorth = !self->movingCarsNorth;
}

void removeCarBridge(Simulation *self) {
    if (self->carsOneBridge > 0) {
        (self->carsOneBridge)--;
    }
}

void removeNorthCars(Simulation *self) {
    if (self->northCarQueue > 0) {
        (self->northCarQueue)--;
    }
}

void removeSouthCars(Simulation *self) {
    if (self->southCarQueue > 0) {
        (self->southCarQueue)--;
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
        (self->carsOneBridge)++;
    
    // Cars going south
    } else {
        SYNC(self, removeSouthCars, NULL);
        (self->carsOneBridge)++;
    }

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

