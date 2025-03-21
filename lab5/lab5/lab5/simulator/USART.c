#include "USART.h"

void USART_Transmit(unsigned char data) {
	/* Wait for empty transmit buffer */
	while ( !( UCSR0A & (1<<UDRE0)) )
	;
	/* Put data into buffer, sends the data */
	UDR0 = data;
}

unsigned char USART_Receive(void) {
	/* Wait for data to be received */
	while ( !(UCSR0A & (1<<RXC0)) )
	;
	/* Get and return received data from buffer */
	return UDR0;
}

unsigned char getUSARTData(USART *self) {
	return self->usartData;
}

void usartMainLoop(USART *self) {
	// Recive the data
	unsigned char dataReceive= USART_Receive();
	self->usartData = dataReceive;
	
	// Transmit data
	unsigned char dataTransmit = SYNC(self->simRef, getData, NULL);
	USART_Transmit(dataTransmit);
	AFTER(MSEC(10), self, usartMainLoop, NULL);
}