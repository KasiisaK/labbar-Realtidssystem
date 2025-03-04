#include <avr/io.h>
#include <stdbool.h>
#include <util/delay.h>

#include "gui.h"
#include "joystickHandler.h"
#include "TinyTimber.h"


// Initialize objects
PortWrite portWriter = initPortWrite();
PulseGen gen1 = initPulseGen(4, &portWriter, true);
PulseGen gen2 = initPulseGen(6, &portWriter, false);
GUI gui = initGUI(&gen1, &gen2);
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
	//freqInit(&gen1);
	//freqInit(&gen2);
    
	
    // Instal interupt handler
    //when the joystick's vertical state changes
    INSTALL(&joystick, joystickInteruptHandler, IRQ_PCINT0);
	INSTALL(&joystick, joystickInteruptHandler, IRQ_PCINT1);
    //when the joystick's horizontal (minus middle) state changes
    
    // Start kernel
    return TINYTIMBER(&BE, NULL, NULL);
}


