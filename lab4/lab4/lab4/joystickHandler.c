#include "TinyTimber.h"
#include "joystickHandler.h"
#include "PulseGen.h"


void joystickInit() {
    // Set 7 to 3 as inputs
    PORTB |= (1 << PB7) | (1 << PB6) | (1 << PB5) | (1 << PB4) | (1 << PB3);
    // Turn on interupts for 0 to 7
    EIMSK |= (1 << PCINT15);

    // Deffine interupts from PB7-3
    PCMSK1 |= (1 << PCINT15) | (1 << PCINT14) | (1 << PCINT12) | (1 << PCINT11) | (1 << PCINT10);
}


// Joystick input handler
void joysticckInteruptHandler(JoystickHandler *self) { 
    // Up
    if((PINB & PB7) >> 7 == 0){
        adjustFrequency(self->gui, 1);
    }
    // Down
    if((PINB & PB7) >> 7 == 0){
        adjustFrequency(self->gui, -1);
    }
    // Left
    if((PINB & PB7) >> 7 == 0){
        swithToLeftGen(self->gui);
    }
    // Right
    if((PINB & PB7) >> 7 == 0){
        swithToRightGen(self->gui);
    }
    // CLick
    if((PINB & PB7) >> 7 == 0){
        saveRestore(self->gui);
    }
}