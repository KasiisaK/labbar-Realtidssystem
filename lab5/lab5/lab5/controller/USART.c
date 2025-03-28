/*
 * USART.c
 *
 * Created: 10/03/2025 11:21:36
 *  Author: AskFr
 */ 
#include "USART.h"
#include <avr/interrupt.h>

#define NORTH_ARVL		0b0001
#define NORTH_BR_ARVL	0b0010
#define SOUTH_ARVL		0b0100
#define SOUTH_BR_ARVL	0b1000

void usart_init(USART *self) {
	UBRR0H = 0;
	UBRR0L = 103; // 9600 baud @ 16MHz
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	mainUSARTLoop(self);
}

unsigned char USART_Receive(void) {
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}

ISR(USART_RX_vect) {
	
}

void mainUSARTLoop(USART *self) {
	while (1) {
		uint8_t data = USART_Receive();
		switch (data)
		{
			case NORTH_ARVL:
				addnorthQ(self->backRef);
				break;
			case NORTH_BR_ARVL:
				addBrdigeQ(self->backRef);
				break;
			case SOUTH_ARVL:
				addsouthQ(self->backRef);
				break;
			case SOUTH_BR_ARVL:
				addBrdigeQ(self->backRef);
				break;
			default:
				break;
		}
		mainSimulation(self->backRef);
	}	
}