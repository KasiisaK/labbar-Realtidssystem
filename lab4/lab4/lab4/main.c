#include <avr/io.h>
#include "joystickHandler.h"
#include "TinyTimber.h"
#include "GUI.h"
#include "PulseGen.h"
#include "PortWrite.h"
#include "joystickHandler.h"

// GUI object
GUI gui = initGUI();

// Global PortWrite object
PortWrite portWriter = initPortWrite();

// JoystickHanlder object
JoystickHandler joystick = initJoystickHandler();

// PulseGen
PulseGen gen1 = initPulseGen(4, &portWriter);
PulseGen gen2 = initPulseGen(6, &portWriter);

// Joystick
...

void sysInit() {
	// Clock Prescale Register "maximum speed"
	CLKPR = 0b10000000; // Clock Prescaler Change Enable
	CLKPR = 0b00000000; // Set 0 for sysclock
	
	// Initialize Port E as output for PE4 and PE6
	DDRE |= (1 << PE4) | (1 << PE6);
}

int main() {
    sysInit();
	
	LCD_init(&gui);
	
	// Install interrupt handler
	INSTALL(&joystick, joystickInteruptHandler, PCINT1_vect)
	
	// Start pulseGen
	ASYNC(&gen1, setFrequency, 1);
	
	// Start kernel
	TINYTIMBER(&gui, updateDisplay, 0);
}


