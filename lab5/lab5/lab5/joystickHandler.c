#include "joystickHandler.h"
#include <util/delay.h>


void joystickInit() {
    // Input for: Down, Up, Click
    PORTB |= (1 << PB7) | (1 << PB6) | (1 << PB4);
    // Input for; Left, Right
    PORTE |= (1 << PE3) | (1 << PE2);
    // Turn on interrupts
    EIMSK |= (1 << PCINT15) | (1 << PCINT14);

    // Define interrupts from PB7,6,4
    PCMSK1 |= (1 << PCINT15) | (1 << PCINT14) | (1 << PCINT12);
    // Define interrupts from PE3,2
    PCMSK0 |= (1 << PCINT3) | (1 << PCINT2);
}


// Joystick input handler
void joystickInteruptHandler(JoystickHandler *self) { 
	
	_delay_ms(100);
	
	// In
	if (!(PINB & (1 << PB4))) {
		
	}
	
	// Right
	if (!(PINE & (1 << PB3))) {
		
	}
	
	// Left
	if (!(PINE & (1 << PB2))) {
		
	}
	
	_delay_ms(900);
	
	// Down
	if (!(PINB & (1 << PB7))) {
		
	}
	
	// Up
	if (!(PINB & (1 << PB6))) {
		
	}	
}