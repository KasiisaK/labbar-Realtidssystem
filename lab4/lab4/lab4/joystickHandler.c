#include "TinyTimber.h"
#include "joystickHandler.h"
#include "PulseGen.h"


void joystickInit(){
    // Enable Pin Change Interrupts for PCMSK1 and PCMSK0
    EIMSK |= (1 << PCIE1) | (1 << PCIE0);

    // Set PB7 (down), PB6 (up), PB1 (left), PB2 (right)
    DDRB &= ~((1 << DDB7) | (1 << DDB6) | (1 << DDB1) | (1 << DDB2));

    // Enable pull-up resistors for the joystick buttons
    PORTB |= (1 << PB7) | (1 << PB6) | (1 << PB1) | (1 << PB2);

    // Enable pin change interrupts for joystick directions
    PCMSK1 |= (1 << PCINT15) | (1 << PCINT14); // PB7 (down), PB6 (up) → PCINT15, PCINT14
    PCMSK0 |= (1 << PCINT1) | (1 << PCINT2);  // PB1 (left), PB2 (right) → PCINT1, PCINT2
}

// Joystick input handler
void joystickInteruptHandler(JoystickHandler *self) {
    // Joystick DOWN pressed
    if (!(PINB & (1 << PB7))) {        
        setFrequency(-1);
    
    // Joystick UP pressed
    } else if (!(PINB & (1 << PB6))) {        
        setFrequency(1);
    
    // Joystick LEFT pressed
    } else if (!(PINB & (1 << PB1))) {        
        leftGen = 1;
    
    // Joystick RIGHT pressed    
    } else if (!(PINB & (1 << PB2))) {        
        leftGen = 0;
    
    } else {
        return; //default
    }
}

void setFrequency(int genValue){

    setFrequency(Gen?, getFreq() + genValue);

}
