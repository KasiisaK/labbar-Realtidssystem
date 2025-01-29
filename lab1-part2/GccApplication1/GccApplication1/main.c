@ -0,0 +1,50 @@
#include <avr/io.h>

#define PRESCALER 256
#define F_CPU 8000000UL // 8 MHz CPU clock
#define TIMER_TICKS_PER_SECOND (F_CPU / PRESCALER)

void init() {
	// Configure the LCD
	CLKPR = 0x80; // Enable clock prescaler change
	CLKPR = 0x00; // Set clock to maximum speed (no prescaler)
	LCDCRB = (1 << LCDCS) | (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0); // Enable LCD and configure
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0); // Set frame rate
	LCDCCR = (1 << LCDDC1) | (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1); // Set drive time and voltage
	LCDCRA = (1 << LCDEN) | (1 << LCDAB); // Enable LCD

	// Configure Timer/Counter1
	TCCR1B = (1 << CS12); // Set prescaler to 256
}

void busyWaitUntil(uint16_t target) {
	while (1) {
		uint16_t current = TCNT1;
		if ((current >= target && target >= current) || // Normal case: target is ahead of current
		(target < current && current < UINT16_MAX)) { // Wraparound case
			break;
		}
	}
}

void blink() {
	uint16_t half_period = TIMER_TICKS_PER_SECOND / 2; // Half the period for 1 Hz blinking
	uint16_t next_timer_value = TCNT1 + half_period;   // Set the initial target time

	while (1) {
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