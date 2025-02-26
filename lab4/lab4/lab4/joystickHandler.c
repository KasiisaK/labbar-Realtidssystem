#include "TinyTimber.h"
#include "joystickHandler.h"
#include "PulseGen.h"


void joystickInit() {
    //sätter på upp, ner och inåt som input
    PORTB = PORTB | 0b11010000;
    //sätter på höger och vänster  som input
    PORTE = PORTE | 0b00001100;
    //DDRE = 0b01010000;
    //sätter på upp,ner,in (15) hög,ven (14) //sida 53 AVr..169 nånitng
    EIMSK = EIMSK | (1<<PCINT15) | (1<<PCINT14);

    //sätter på upp, ner och inåt på joystick (som interrupt)
    PCMSK1 = PCMSK1 | (1<<PCINT15) | (1<<PCINT14) | (1<<PCINT12);
    //sätter på höger och vänster på joystick (som interrupt)
    PCMSK0 = PCMSK0 | (1<<PCINT3) | (1<<PCINT2);
}


// Joystick input handler
void interruptPinB(JoystickHandler *self) { 
    if((PINB & 0b10000000) >> 7 == 0){ //down press on joystick
        adjustFrequency(self->gui, -1);
    }

    if((PINB & 0b01000000) >> 6 == 0){ //up press on joystick
        adjustFrequency(self->gui, 1);
    }

    if((PINB & 0b00010000) >> 4 == 0){ //middle press
        saveRestore();
    }
}

void interruptPinE(JoystickHandler *self) {  
    if((PINE & 0b00000100) >> 2 == 0){ //left press
       // ASYNC(self->gui, switchFocus, 0);
    }

    if((PINE & 0b00001000) >> 3 == 0){  //right press
       // ASYNC(self->gui, switchFocus, 1);
    }
}