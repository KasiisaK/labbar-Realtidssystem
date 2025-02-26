#include "TinyTimber.h"
#include "joystickHandler.h"
#include "PulseGen.h"


void joystickInit() {
    // Input for: Down, Up, Click
    PORTB |= (1 << PB7) | (1 << PB6) | (1 << PB4);
    //Input for; Left, Right
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
        adjustFrequency(self->gui, -1);
    }
    // Up
    if (!(PINB & (1 << PB6))) {
        adjustFrequency(self->gui, 1);
    }
    // In
    if (!(PINB & (1 << PB4))) {
        saveRestore(self->gui);
    }
    // ...
    if((PINE & 0b00000100) >> 2 == 0) {
        swithToLeftGen(self->gui);
    }
    // ...
    if((PINE & 0b00001000) >> 3 == 0) {
        swithToRightGen(self->gui);
    }
}