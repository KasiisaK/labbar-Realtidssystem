/*
 * lab5.c
 *
 * Created: 2022-03-08 14:39:06
 * Author : simeng-0
 */ 

#include <avr/io.h>
#include "main.h"


Lights lights = initLights();
Road road = initRoad(&lights);
GUI gui = initGUI(&road);
Backend backend = initBackend(&gui, &road);
InterruptHandler handler = initHandler(&backend);


void init(){
	CLKPR = 0x80;
	CLKPR = 0x00;
	LCDCRB = (1<<LCDCS) | (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM1) | (1<<LCDPM0);
	LCDFRR = (1<<LCDCD2) | (1<<LCDCD1) | (1<<LCDCD0);
	LCDCCR = (1<<LCDDC1) | (1<<LCDCC3) | (1<<LCDCC2) | (1<<LCDCC1);
	TCCR1A = (1<<WGM13) | (1<<WGM12) | (1<<COM1A1) | (1<<COM1A0);
	LCDCRA = (1<<LCDEN) | (1<<LCDAB);
	
	cli();
	//USART init
	UBRR0L = 51; // set baud rate to 9600 bps for f=8 MHz, u2x=0, see p.176
	UCSR0B = (1<<RXEN0) | (1<<TXEN0) | (1<<RXCIE0) | (1<<TXCIE0) /*| (1<<UDRIE0)*/; //enable receiver and transmitter, enable reciever and transmitter interrupt
	UCSR0C = (1<<UCSZ00) | (1<<UCSZ01); // set 8-bit word
	sei();
}
	

int main(void)
{
	init();
	// install interrupt
	INSTALL(&handler, receiveInterrupt, IRQ_USART0_RX);
	INSTALL(&handler, transmitInterrupt, IRQ_USART0_TX);
	//INSTALL(&handler, regEmptyInterrupt, IRQ_USART0_UDRE);
	return TINYTIMBER(&backend, start, 0);
	
    /* Replace with your application code */
	
	/*
	//LCDDR0 = LCDDR0 ^ 0xFF;
	UDR0='y';
	//UDR0='e';
	//UDR0='e';
	UDR0='t';
	char testing = UDR0;
	//UDR0='a';
    while ( !(UCSR0A & (1<<UDRE0) )) {}
		UDR0 = 'a';
	while ( !(UCSR0A & (1<<UDRE0) )) {}
		UDR0 = 'b';
	while ( !(UCSR0A & (1<<UDRE0) )) {}
		UDR0 = 'c';
	while ( !(UCSR0A & (1<<UDRE0) )) {}
		UDR0 = 'd';
		*/
}

