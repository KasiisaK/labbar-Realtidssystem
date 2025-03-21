#include "TinyTimber.h"
#include <pthread.h>

typedef struct {
	Object super;
	Input_handler *handlerRef;
	Simulation *simRef;
	unsigned char usartData;
} USART;

#define initUSART(handlerRef, simRef) \
{initObject(), NULL, handlerRef, simRef, 0b0000}
	
void USART_Transmit(unsigned char data);
unsigned char USART_Receive(void);

unsigned char getUSARTData(USART *self);

void usartMainLoop(USART *self);