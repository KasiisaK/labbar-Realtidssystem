#include "tinythreads.h"
#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>

// Global variable to simulate a shared resource
int pp = 0;

// Mutex to protect the critical section
mutex pp_mutex = MUTEX_INIT;

void init() {
	// Clock Prescale Register "maximum speed"
	CLKPR = 0b10000000; // Clock Prescaler Change Enable
	CLKPR = 0b00000000; // Set 0 for sysclock
}

void LCD_init() {
	// LCD(Contrast Control Register), LCD(Display Configuration)(000): 300 Î¼s, LCD(Contrast Control)(1111): 3.35 V
	LCDCCR = (0 << LCDDC0) | (0 << LCDDC1) | (0 << LCDDC2) | (1 << LCDCC0) | (1 << LCDCC1) | (1 << LCDCC2) | (1 << LCDCC3);
	// LCDCS: asynchronous clock, LCDMUX(11): D=1/4, B=1/3, LCD(Port Mask): 25 segments
	LCDCRB = (1 << LCDCS) | (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0);
	// LCD(Clock Divide)(111): (D=8) 32Hz
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	// LCD(Control and Status Register A), LCD(Enable): True, LCD(Low Power Waveform): True, (no frame interrupt, no blanking)
	LCDCRA = (1 << LCDEN) | (1 << LCDAB);
}

// Wall of data
int zero[] = {0b0001, 0b0101, 0b0101, 0b0001};
int one[] = {0b0000, 0b0001, 0b0001, 0b0000};
int two[] = {0b0001, 0b0001, 0b1110, 0b0001};
int three[] = {0b0001, 0b0001, 0b1011, 0b0001};
int four[] = {0b0000, 0b0101, 0b1011, 0b0000};
int five[] = {0b0001, 0b0100, 0b1011, 0b0001};
int six[] = {0b0001, 0b0100, 0b1111, 0b0001};
int seven[] = {0b0001, 0b0001, 0b0001, 0b0000};
int eight[] = {0b0001, 0b0101, 0b1111, 0b0001};
int nine[] = {0b0001, 0b0101, 0b1011, 0b0001};
int none[] = {0b0000, 0b0000, 0b0000, 0b0000};

// Returns wall of data based on char input ('0' = 48 (char))
int* getSegmentForChar(char ch) {
	switch (ch) {
		case '0': return zero;
		case '1': return one;
		case '2': return two;
		case '3': return three;
		case '4': return four;
		case '5': return five;
		case '6': return six;
		case '7': return seven;
		case '8': return eight;
		case '9': return nine;
		default:  return none;
	}
}

void writeChar(char ch, uint8_t pos) {
	// Check if outside range
	if (pos > 4 || pos < 0) return;

	// Get correct char data
	int* segment = getSegmentForChar(ch);

	// Choose position
	switch (pos) {
		case 0:
		// Segment start at 0, 5, 10, 15, higher 4 bits.
		// (LCDDR0 & 0xF0) clears the segment before writing
		LCDDR0 = (LCDDR0 & 0xF0) | segment[0];
		LCDDR5 = (LCDDR5 & 0xF0) | segment[1];
		LCDDR10 = (LCDDR10 & 0xF0) | segment[2];
		LCDDR15 = (LCDDR15 & 0xF0) | segment[3];
		break;
		case 1:
		// Same segment just lower 4 bits
		LCDDR0 = (LCDDR0 & 0x0F) | (segment[0] << 4);
		LCDDR5 = (LCDDR5 & 0x0F) | (segment[1] << 4);
		LCDDR10 = (LCDDR10 & 0x0F) | (segment[2] << 4);
		LCDDR15 = (LCDDR15 & 0x0F) | (segment[3] << 4);
		break;
		case 2:
		LCDDR1 = (LCDDR1 & 0xF0) | segment[0];
		LCDDR6 = (LCDDR6 & 0xF0) | segment[1];
		LCDDR11 = (LCDDR11 & 0xF0) | segment[2];
		LCDDR16 = (LCDDR16 & 0xF0) | segment[3];
		break;
		case 3:
		LCDDR1 = (LCDDR1 & 0x0F) | (segment[0] << 4);
		LCDDR6 = (LCDDR6 & 0x0F) | (segment[1] << 4);
		LCDDR11 = (LCDDR11 & 0x0F) | (segment[2] << 4);
		LCDDR16 = (LCDDR16 & 0x0F) | (segment[3] << 4);
		break;
		case 4:
		LCDDR2 = (LCDDR2 & 0xF0) | segment[0];
		LCDDR7 = (LCDDR7 & 0xF0) | segment[1];
		LCDDR12 = (LCDDR12 & 0xF0) | segment[2];
		LCDDR17 = (LCDDR17 & 0xF0) | segment[3];
		break;
	}
}

bool is_prime(int number) {
	// 0 and 1 are not prime numbers
	if (number <= 1) return false;

	// Loop from 2 to sqrt(number)
	for (int i = 2; i * i <= number; i++) {
		if (number % i == 0) return false; // Divisible => not prime
	}
	// Is prime if no factors
	return true;
}

void printAt(long num, int pos) {
	lock(&pp_mutex); // Lock the mutex to protect the critical section

	// Use the global pp variable
	pp = pos;
	writeChar((num % 100) / 10 + '0', pp);
	pp++;
	writeChar(num % 10 + '0', pp);

	// Optional: Add a delay loop to increase the chance of context switching
	volatile int i;
	for (i = 0; i < 1000; i++); // Delay loop

	unlock(&pp_mutex); // Unlock the mutex
}

void computePrimes(int pos) {
	long n;

	for (n = 1; ; n++) {
		if (is_prime(n)) {
			printAt(n, pos);
			_delay_ms(5000);
		}
	}
}

int main() {
	init();
	LCD_init();
	spawn(computePrimes, 0);
	computePrimes(3);
}