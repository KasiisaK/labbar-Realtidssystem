#include "simulation.h"
#include <stdbool.h>

// Get output for USART to send to avr
unsigned char getData(Simulation *self) {
	return self->output;
}

// Bridge North
void addNorthCarBridge(Simulation *self) {
	pthread_mutex_lock(&(self->bridgeMtx));
	(self->carsGoingNorth)++;
	// Bit 1: Northbound bridge entry sensor activated
	self->output |= 0b0100;
	pthread_mutex_unlock(&(self->bridgeMtx));
}
void removeNorthCarBridge(Simulation *self) {
	if (self->carsGoingNorth > 0) {
		pthread_mutex_lock(&(self->bridgeMtx));
		(self->carsGoingNorth)--;
		pthread_mutex_unlock(&(self->bridgeMtx));
	}
}
// Bridge South
void addSouthCarBridge(Simulation *self) {
    pthread_mutex_lock(&(self->bridgeMtx));
    (self->carsGoingSouth)++;
	// Bit 3: Southbound bridge entry sensor activated
	self->output |= 0b0001;
    pthread_mutex_unlock(&(self->bridgeMtx));
}
void removeSouthCarBridge(Simulation *self) {
    if (self->carsGoingSouth > 0) {
        pthread_mutex_lock(&(self->bridgeMtx));
        (self->carsGoingSouth)--;
        pthread_mutex_unlock(&(self->bridgeMtx));
    }
}

// North
void addCarNorth(Simulation *self) {
    pthread_mutex_lock(&(self->northMtx));
    (self->northCarQueue)++;
	// Bit 0: Northbound car arrival sensor activated
	self->output |= 0b1000;
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
	// Bit 2: Southbound car arrival sensor activated
	self->output |= 0b0010;
    pthread_mutex_unlock(&(self->southMtx));
}
void removeSouthCars(Simulation *self) {
    if (self->southCarQueue > 0) {
        pthread_mutex_lock(&(self->southMtx));
        (self->southCarQueue)--;
        pthread_mutex_unlock(&(self->southMtx));
    }
}

void procesUSARTData(Simulation *self) {
	unsigned char usartData = getUSARTData(self->usartRef);

	// Northbound light handling
	if (usartData & 0b1000)
		// Green light
		self->movingCarsNorth = true;  
		} else if (usartData & 0b0100) {
		// Red light
		self->movingCarsNorth = false;
	}

	// Southbound light handling
	if (usartData & 0b0010) {
		// Green light
		self->movingCarsSouth = true;
		} else if (usartData & 0b0001) {
		// Red light
		self->movingCarsSouth = false; 
	}

}

void mainSimulationLoop(Simulation *self) {
    // Get North/South Light status from USART
	procesUSARTData(self->usartRef); //vetej
	
    // North Cars
    if (getNorthLightStatus(self->usartRef)) {
		// Remove from queue, add to bridge
        removeNorthCars(self);
		addNorthCarBridge(self);
		// Remove car from bridge after 5 sec
		AFTER(SEC(5), self, removeNorthCarBridge, NULL);
    }
	// South Cars
    if (SYNC(self->bridgeObj, getSouthLightStatus, NULL)) {
		// Remove from queue, add to bridge
        removeSouthCars(self);
		addSouthCarBridge(self);
		// Remove car from bridge after 5 sec
		AFTER(SEC(5), self, removeSouthCarBridge, NULL);
    }     

	// Reset output for next loop
	self->output = 0b0000;
    // A car passed every second so call loop every second
    AFTER(SEC(1), self, mainSimulationLoop, NULL);
}

