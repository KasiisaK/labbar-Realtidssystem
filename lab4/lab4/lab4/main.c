#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "gui.h"
#include "joystickHandler.h"
#include "TinyTimber.h"
#include "Backend.h"


// Initialize objects
PortWrite portWriter = initPortWrite();
PulseGen gen1 = initPulseGen(4, &portWriter);
PulseGen gen2 = initPulseGen(6, &portWriter);
GUI gui = initGUI(&gen1, &gen2, true);
Backend BE = initBackend(&gen1, &gen2, &gui);
JoystickHandler joystick = initJoystickHandler(&BE);

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

	
    // Install interrupt handler
    INSTALL(&joystick, joystickInteruptHandler, IRQ_PCINT0);
	INSTALL(&joystick, joystickInteruptHandler, IRQ_PCINT1);
    
    // Start kernel
    return TINYTIMBER(&BE, startProgram, NULL);
}


