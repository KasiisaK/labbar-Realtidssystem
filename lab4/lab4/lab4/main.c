#include <avr/io.h>
#include "gui.h"
#include "joystickHandler.h"
#include "TinyTimber.h"


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
    sysInit();
    pinOutputInit();
    joystickInit();
    LCD_init();
    
    // Instal interupt handler
    //when the joystick's vertical state changes
    INSTALL(&joystick, interruptPinB, IRQ_PCINT1);
    //when the joystick's horizontal (minus middle) state changes
    INSTALL(&joystick, interruptPinE, IRQ_PCINT0);
    
    // Start kernel
    return TINYTIMBER(&gui, NULL, NULL);
}


