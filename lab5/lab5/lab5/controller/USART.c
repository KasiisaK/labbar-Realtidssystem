/*
 * USART.c
 *
 * Created: 10/03/2025 11:21:36
 *  Author: AskFr
 */ 
#include "USART.h"
#include <avr/interrupt.h>

extern USART usart; // Declare global instance

void usart_init(USART *self) {
	UBRR0H = 0;
	UBRR0L = 103; // 9600 baud @ 16MHz
	UCSR0B = (1 << RXEN0) | (1 << TXEN0) | (1 << RXCIE0);
	UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

void usart_send(USART *self, uint8_t data) {
	while (!(UCSR0A & (1 << UDRE0)));
	UDR0 = data;
}

ISR(USART_RX_vect) {
	uint8_t sensor_data = UDR0;
	ASYNC(usart.trafficLight, handleSensor, sensor_data);
}