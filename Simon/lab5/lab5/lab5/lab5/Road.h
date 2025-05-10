/*
 * Road.h
 *
 * Created: 2022-03-08 14:57:01
 *  Author: simeng-0
 */ 



#ifndef ROAD_H_
#define ROAD_H_

#include "TinyTimber.h"
#include "Lights.h"

#define initRoad(l) { initObject(), l, 0, 0, 0, 'p', 15, 0, 1, 0, 'y' }

typedef struct  {
	Object super;
	Lights *lights;
	int northBound;
	int southBound;
	int onBridge;
	char direction;
	int carsLeftUntilChange; //start 15
	int carsSent; // set 0 in init
	int paused;
	int wantToChangeDirection;
	char canAllowNew;
	Msg currMsg;
} Road;

void updateSignal(Road *self);
void driveNorth(Road *self);
void driveSouth(Road *self);
void redBoth(Road *self);
void newNorthBound(Road *self);
void newSouthBound(Road *self);
int getNorthBound(Road *self);
int getSouthBound(Road *self);
int getOnBridge(Road* self);
void northToBridge(Road *self);
void southToBridge(Road *self);
void exitBridge(Road *self);

#endif /* ROAD_H_ */