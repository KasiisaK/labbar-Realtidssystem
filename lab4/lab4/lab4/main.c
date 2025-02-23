#include <avr/io.h>
#include "gui.h"
#include "joystickHandler.h"

// Initialize objects
PortWrite portWriter = initPortWrite();
PulseGen gen1 = initPulseGen(4, &portWriter);
PulseGen gen2 = initPulseGen(6, &portWriter);
GUI gui = initGUI(&gen1, &gen2);
JoystickHandler joystick = initJoystickHandler(&gui);

int main() {
    sysInit();
    joystickInit();
    
    // Initial frequencies
    ASYNC(&gen1, setFrequency, 1);
    ASYNC(&gen2, setFrequency, 1);
    
    // Start GUI
    ASYNC(&gui, updateDisplay, 0);
    
    // Start kernel
    TINYTIMBER(&joystick, joystickInterruptHandler, 0);
}


