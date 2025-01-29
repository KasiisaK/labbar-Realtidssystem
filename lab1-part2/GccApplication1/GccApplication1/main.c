#include <avr/io.h>

#define PRESCALER 256
#define F_CPU 8000000UL // 8 MHz CPU clock
#define TIMER_TICKS_PER_SECOND (F_CPU / PRESCALER)

void init() {
	//Clock Prescale Register "maximum speed"
	CLKPR = 0b10000000; //Clock Prescaler Change Enable
	CLKPR = 0b00000000; //set 0 for sysclock
	//LCD(Contrast Control Register), LCD(Display Configuration)(000): 300 μs, LCD(Contrast Control)(1111): 3.35 V
	LCDCCR = (0 << LCDDC0) | (0 << LCDDC1) | (0 << LCDDC2) | (1 << LCDCC0) | (1 << LCDCC1) | (1 << LCDCC2) | (1 << LCDCC3);
	//LCDCS: asynchronous clock, LCDMUX(11): D=1/4, B=1/3, LCD(Port Mask): 25 segments
	LCDCRB = (1 << LCDCS) | (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0);
	//LCD(Clock Divide)(111): (D=8) 32Hz 
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);	
	//LCD(Control and StatusRegister A), LCD(Enable): True, LCD(Low Power Waveform): True, (no frame interrupt, no blanking)
	LCDCRA = (1 << LCDEN) | (1 << LCDAB);

	// Configure Timer/Counter1
	TCCR1B = (1 << CS12); // Set prescaler to 256
}

void busyWaitUntil(uint16_t target) {
	while (((int16_t)(TCNT1 - target)) < 0) {
	}
}

void blink() {
	uint16_t half_period = (TIMER_TICKS_PER_SECOND * 1) / 2; // Half the period for 1 Hz blinking
	static uint16_t next_timer_value = 0;   // Set the initial target time
	while (1)
	{
		if (next_timer_value == 0) {
		next_timer_value = TCNT1 + half_period;
		}
	
		// Toggle the segment (replace LCDDR0 and bit as needed for the actual segment)
		LCDDR0 ^= (1 << 1);

		// Wait for the next half period
		busyWaitUntil(next_timer_value);

		// Update the next target time, accounting for wraparound
		next_timer_value += half_period;
	}
	
	

}

int main(void) {
	init(); // Initialize the device
	blink(); // Start blinking the segment
	return 0;
}