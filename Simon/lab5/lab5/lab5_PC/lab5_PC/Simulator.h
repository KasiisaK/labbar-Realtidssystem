/*
 * Simulator.h
 *
 * Created: 2022-03-12 15:41:20
 *  Author: simeng-0
 */ 


#ifndef SIMULATOR_H_
#define SIMULATOR_H_

typedef struct  {
		int northBound;
		int southBound;
		int onBridge;
		char direction;
		int carsLeftUntilChange; //start 15
} Simulator;



#endif /* SIMULATOR_H_ */