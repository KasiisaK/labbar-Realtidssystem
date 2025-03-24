#include "simulation.h"
#include <stdbool.h>
#include <termios.h>
#include <pthread.h>
#include <unistd.h> // usleep()

/*
Bit 0: Northbound car arrival sensor activated
Bit 1: Northbound bridge entry sensor activated
Bit 2: Southbound car arrival sensor activated
Bit 3: Southbound bridge entry sensor activated
*/
#define NORTH_ARVL		0b0001
#define NORTH_BR_ARVL	0b0010
#define SOUTH_ARVL		0b0100
#define SOUTH_BR_ARVL	0b1000

/*
Bit 0: Northbound green light status
Bit 1: Northbound red light status
Bit 2: Southbound green light status
Bit 3: Southbound red light status
*/
#define NORTH_GREEN 0b0001
#define NORTH_RED	0b0010
#define SOUTH_GREEN 0b0100
#define SOUTH_RED   0b1000

// Print out simulation state
void printState(Simulation *self) {
	pthread_mutex_lock(&(self->northMtx));
	pthread_mutex_lock(&(self->southMtx));
	pthread_mutex_lock(&(self->bridgeMtx));
	printf("North cars que: %d, North cars bridge %d.\n", self->northCarQueue, self->carsGoingNorth);
	printf("South cars que: %d, South cars bridge %d.\n", self->southCarQueue, self->carsGoingSouth);
	printf("North light status: %d, South light status: %d", getNorthLightStatus(self->bridgeObj), getSouthLightStatus(self->bridgeObj));
	pthread_mutex_unlock(&(self->bridgeMtx));
	pthread_mutex_unlock(&(self->southMtx));
	pthread_mutex_unlock(&(self->northMtx));
}

// Get output data to send to avr
unsigned char getData(Simulation *self) {
	unsigned char data = self->output;
	self->output = 0b0000; // Reset data once retrived 
	return data;
}

// Bridge North
void addNorthCarBridge(Simulation *self) {
	pthread_mutex_lock(&(self->bridgeMtx));
	(self->carsGoingNorth)++;
	self->output |= NORTH_BR_ARVL;
	pthread_mutex_unlock(&(self->bridgeMtx));
}
void removeNorthCarBridge(Simulation *self) {
	// Remove car after 5 sec
	usleep(5000000);
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
	self->output |= SOUTH_BR_ARVL;
    pthread_mutex_unlock(&(self->bridgeMtx));
}
void removeSouthCarBridge(Simulation *self) {
	// Remove car after 5 sec
	usleep(5000000);
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
	self->output |= NORTH_ARVL;
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
	self->output |= SOUTH_ARVL;
    pthread_mutex_unlock(&(self->southMtx));
}
void removeSouthCars(Simulation *self) {
    if (self->southCarQueue > 0) {
        pthread_mutex_lock(&(self->southMtx));
        (self->southCarQueue)--;
        pthread_mutex_unlock(&(self->southMtx));
    }
}

// Update bridge class based on AVR USART data
void procesUSARTData(Simulation *self) {
	unsigned char usartData = getUSARTData(self->readerRef);

	if (usartData & (1 << 0)){
		changeLightState(self->bridgeObj, NORTH_GREEN);
	}
	if (usartData & (1 << 1)){
		changeLightState(self->bridgeObj, NORTH_RED);
	}
	if (usartData & (1 << 2)){
		changeLightState(self->bridgeObj, SOUTH_GREEN);
	}
	if (usartData & (1 << 3)){
		changeLightState(self->bridgeObj, SOUTH_RED);
	}
}

void mainSimulationLoop(Simulation *self) {
	while(1) {
        // Get North/South Light status from USART
		procesUSARTData(self);
		
		pthread_t carLeaving; // Schedule removal of cars in new thread

		// North Cars
		if (getNorthLightStatus(self->bridgeObj)) {
			// Remove from queue, add to bridge
			removeNorthCars(self);
			addNorthCarBridge(self);
			// Remove car from bridge after 5 sec
			pthread_create(&carLeaving, NULL, (void *)removeNorthCarBridge, self);
			pthread_detach(carLeaving);
		}
		// South Cars
		if (getSouthLightStatus(self->bridgeObj)) {
			// Remove from queue, add to bridge
			removeSouthCars(self);
			addSouthCarBridge(self);
			// Remove car from bridge after 5 sec
			pthread_create(&carLeaving, NULL, (void *)removeSouthCarBridge, self);
			pthread_detach(carLeaving);
		}     
		// Send data to AVR
		write(self->port_fd, &(getData(self)), 1);
		printState(self);

		// A car passed every second so call loop every second
		usleep(1000000);
    }
}

