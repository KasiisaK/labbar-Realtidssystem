#include <avr/io.h>

#include "TinyTimber.h"
#include "GUI.h"

//GUI object
GUI gui = initGUI();

int main() {
    return TINYTIMBER(&gui, updateDisplay, 0);
}


