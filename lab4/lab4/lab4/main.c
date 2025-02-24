#include <avr/io.h>
#include "gui.h"
#include "joystickHandler.h"


// Initialize objects
PortWrite portWriter = initPortWrite();
PulseGen gen1 = initPulseGen(4, &portWriter);
PulseGen gen2 = initPulseGen(6, &portWriter);
GUI gui = initGUI(&gen1, &gen2);
JoystickHandler joystick = initJoystickHandler(&gui);

void sysInit(){
    // Clock Prescale Register "maximum speed"
	CLKPR = 0b10000000; // Clock Prescaler Change Enable
	CLKPR = 0b00000000; // Set 0 for sysclock
}

void pinOutputInit(){
    // Initialize Port E as output for PE4 and PE6
	DDRE |= (1 << PE4) | (1 << PE6);
}


int main() {
    // All Inits
    cli();
    sysInit();
    pinOutputInit();
    joystickInit();
    LCD_init();
    sei();
    
    // Instal interupt handler
    INSTALL(&joystick, joystickInterruptHandler, PCINT1_vect);
    
    // Start kernel
    return TINYTIMBER(&gui, NULL, NULL);
}


