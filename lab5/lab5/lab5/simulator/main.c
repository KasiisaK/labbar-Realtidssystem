#include <avr/io.h>
#include <pthread.h>

#include "input_handler.h"

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void USART_Init(unsigned int ubrr) {
// Set baud rate
UBRRH0 = (unsigned char)(ubrr>>8);
UBRRL0 = (unsigned char)ubrr;
// Enable receiver and transmitter
UCSR0B = (1<<RXEN0)|(1<<TXEN0);
// Set frame format: 8data, 2stop bit
UCSRnC = (0<<USBS0)|(3<<UCSZ00);
}


void main() {
    USART_Init(MYUBRR);

    pthread_t inputThread;

    pthread_create(inputThread, NULL, getUserInput, NULL);

}