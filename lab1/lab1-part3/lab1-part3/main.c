/*
 * lab1-part3.c
 *
 * Created: 28/01/2025 13:39:36
 * Author : AskFr
 */ 

#include <avr/io.h>
#include <stdlib.h>
#include <stdbool.h>
#include <util/delay.h>

#define LCD_SEGMENT1 0b00000001 //  segment 1
#define LCD_SEGMENT2 0b00100000 //  segment 2

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

	// Configure bit 7 of PORTB as input and enable pull-up resistor
	DDRB &= ~(1 << PB7);
	PORTB |= (1 << PB7);

}

// Toggle between two LCD segments
void toggle_lcd(uint8_t *current_segment) {
	if (*current_segment == LCD_SEGMENT1) {
		*current_segment = LCD_SEGMENT2;
		// Clear LCD segment 1
		LCDDR3 &= ~LCD_SEGMENT1;
		// Update to LCD segment 2
		LCDDR2 = (LCDDR2 & 0xFF) | LCD_SEGMENT2;
		} else {
		*current_segment = LCD_SEGMENT1;
		// Clear LCD segment 2
		LCDDR2 &= ~LCD_SEGMENT2;
		// Update to LCD segment 1
		LCDDR3 = (LCDDR3 & 0xFF) | LCD_SEGMENT1;
	}
}

void button() {
	static uint8_t current_segment = LCD_SEGMENT1;
	uint8_t joystick_pressed = 0;                 

	while (true) {
		// Check if joystick is pressed (active low, bit 7 of PINB == 0)
		if (!(PINB & (1 << PB7))) {
			if (!joystick_pressed) {
				joystick_pressed = 1;

				toggle_lcd(&current_segment);
			}
			} else {
			joystick_pressed = 0;
		}

		_delay_ms(100);
	}
}

int main(void) {
	init();

	button();

	return 0;
}
