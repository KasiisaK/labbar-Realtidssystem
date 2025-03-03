#include <avr/io.h>
#include "gui.h"
#include "joystickHandler.h"
#include "TinyTimber.h"
#include <stdbool.h>


// Initialize objects
PortWrite portWriter = initPortWrite();
PulseGen gen1 = initPulseGen(4, &portWriter, true);
PulseGen gen2 = initPulseGen(6, &portWriter, false);
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
    sysInit();
    pinOutputInit(); // Is this needed
    joystickInit();
    LCD_init();
	//freqInit(&gen1);
	//freqInit(&gen2);
    

	while (1) {
		PORTE ^= (1 << 6);
		_delay_ms(500);
	}

	/*
	
    // Instal interupt handler
    //when the joystick's vertical state changes
    INSTALL(&joystick, joysticckInteruptHandler, IRQ_PCINT0);
	INSTALL(&joystick, joysticckInteruptHandler, IRQ_PCINT1);
    //when the joystick's horizontal (minus middle) state changes
    
    // Start kernel
    return TINYTIMBER(&gui, NULL, NULL);
	*/
}


