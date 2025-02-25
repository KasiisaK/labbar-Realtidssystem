#include "TinyTimber.h"
#include "joystickHandler.h"
#include "PulseGen.h"


void joystickInit() {
    // Enable Pin Change Interrupts for PCINT[7:0] (PCIE0)
    PCICR |= (1 << PCIE0); // Enable Pin Change Interrupts for PCMSK0

    // Enable input for PB7 (Up), PB6 (Down), PB1 (Left), PB2 (Right), PB5 (Click)
    DDRB &= ~((1 << DDB7) | (1 << DDB6) | (1 << DDB1) | (1 << DDB2) | (1 << DDB5));

    // Enable pull-up resistors for joystick buttons (assuming active-low)
    PORTB |= (1 << PB7) | (1 << PB6) | (1 << PB1) | (1 << PB2) | (1 << PB5);

    // Enable pin change interrupts for joystick directions
    PCMSK0 |= (1 << PCINT7) | (1 << PCINT6); // PB7 (up), PB6 (down) => PCINT7, PCINT6
    PCMSK0 |= (1 << PCINT1) | (1 << PCINT2); // PB1 (left), PB2 (right) => PCINT1, PCINT2
    PCMSK0 |= (1 << PCINT5);                 // PB5 (click) => PCINT5
}


// Joystick input handler
void joystickInterruptHandler(JoystickHandler *self) {
    if (!(PINB & (1 << PB2))) {        // RIGHT
        ASYNC(self->gui, switchFocus, 1);
    } else if (!(PINB & (1 << PB1))) { // LEFT
        ASYNC(self->gui, switchFocus, 0);
    } else if (!(PINB & (1 << PB6))) { // UP
        ASYNC(self->gui, adjustFrequency, 1);
    } else if (!(PINB & (1 << PB7))) { // DOWN
        ASYNC(self->gui, adjustFrequency, -1);
    } else if (!(PINB & (1 << PB5))) {
        ASYNC(self->gui, saveRestore, 0);
    }
}
