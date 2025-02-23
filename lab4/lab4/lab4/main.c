#include <avr/io.h>

#include "TinyTimber.h"
#include "GUI.h"
#include "PulseGen.h"
#include "PortWrite.h"

// GUI object
GUI gui = initGUI();

// Global PortWrite object
PortWrite portWriter = initPortWrite();

// PulseGen
PulseGen gen1 = initPulseGen(4, &portWriter);
PulseGen gen2 = initPulseGen(6, &portWriter);

ASYNC(&gen1, setFrequency(1));

void init() {
	// Clock Prescale Register "maximum speed"
	CLKPR = 0b10000000; // Clock Prescaler Change Enable
	CLKPR = 0b00000000; // Set 0 for sysclock
}

void LCD_init() {
	// LCD(Contrast Control Register), LCD(Display Configuration)(000): 300 s, LCD(Contrast Control)(1111): 3.35 V
	LCDCCR = (0 << LCDDC0) | (0 << LCDDC1) | (0 << LCDDC2) | (1 << LCDCC0) | (1 << LCDCC1) | (1 << LCDCC2) | (1 << LCDCC3);
	// LCDCS: asynchronous clock, LCDMUX(11): D=1/4, B=1/3, LCD(Port Mask): 25 segments
	LCDCRB = (1 << LCDCS) | (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0);
	// LCD(Clock Divide)(111): (D=8) 32Hz
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	// LCD(Control and Status Register A), LCD(Enable): True, LCD(Low Power Waveform): True, (no frame interrupt, no blanking)
	LCDCRA = (1 << LCDEN) | (1 << LCDAB);
}


int main() {
    // Initialize Port E as output for PE4 and PE6
    DDRE |= (1 << PE4) | (1 << PE6);
	INSTALL(&gui, );
	TINYTIMBER(&gui, updateDisplay, 0);
}


