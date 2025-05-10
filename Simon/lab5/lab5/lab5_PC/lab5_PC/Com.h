/*
 * Com.h
 *
 * Created: 2022-03-11 14:06:57
 *  Author: simeng-0
 */ 


#ifndef COM_H_
#define COM_H_

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h> //sleep
#include <pthread.h>


#include <fcntl.h>
#include <errno.h> 
#include <termios.h> 
#include <unistd.h>

#define initCom() {}

typedef struct  {
	int* port;
} Com;

//FILE *fileP;

int serial;

void initCom();
void listen();
void writeToPort();



#endif /* COM_H_ */