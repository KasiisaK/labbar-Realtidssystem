#include "TinyTimber.h"
#include "joystickHandler.h"
#include "PulseGen.h"


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
void joysticckInteruptHandler(JoystickHandler *self) { 
    // Down
    if (!(PINB & (1 << PB7))) {
		ASYNC(self, holdDown, 0);
	    //holdDown(self);
    }
    // Up
    if (!(PINB & (1 << PB6))) {
        ASYNC(self, holdUp, 0);
		//holdUp(self);
    }
    // In
    if (!(PINB & (1 << PB4))) {
        ASYNC(self->gui, saveRestore, 0);
		//saveRestore(self->gui);
    }
    // Left
    if (!(PINE & (1 << PB2))) {
        ASYNC(self->gui, swithToLeftGen, 0);
		//swithToLeftGen(self->gui);
    }
    // Right
    if (!(PINE & (1 << PB3))) {
        ASYNC(self->gui, swithToRightGen, 0);
		//swithToRightGen(self->gui);
    }
}

void holdDown(JoystickHandler *self) {
	if (!(PINB & (1 << PB7))) {
		SYNC(self->gui, adjustFrequency, -1);
        AFTER(MSEC(500), self, holdDown, 0);
	}
}

void holdUp(JoystickHandler *self) {
    // If holding down (up) key
    if (!(PINB & (1 << PB6))) {
        SYNC(self->gui, adjustFrequency, 1);
        AFTER(MSEC(500), self, holdUp, 0);
    }
}
