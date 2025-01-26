#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>


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


void init() {
	CLKPR = 0x80;
	CLKPR = 0x00;
	LCDCRB = (1 << LCDCS) | (1 << LCDMUX1) | (1 << LCDMUX0) | (1 << LCDPM2) | (1 << LCDPM1) | (1 << LCDPM0);
	LCDFRR = (1 << LCDCD2) | (1 << LCDCD1) | (1 << LCDCD0);
	LCDCCR = (1 << LCDDC1) | (1 << LCDCC3) | (1 << LCDCC2) | (1 << LCDCC1);
	TCCR1A = (1 << WGM13) | (1 << WGM12) | (1 << COM1A1) | (1 << COM1A0);
	LCDCRA = (1 << LCDEN) | (1 << LCDAB);
}


void writeChar(char ch, uint8_t pos) {
	if (pos > 4 || pos < 0) return;
	

	int* segment = getSegmentForChar(ch);
	
	switch (pos) {
		case 0:
			LCDDR0 = (LCDDR0 & 0xF0) | segment[0];
			LCDDR5 = (LCDDR5 & 0xF0) | segment[1];
			LCDDR10 = (LCDDR10 & 0xF0) | segment[2];
			LCDDR15 = (LCDDR15 & 0xF0) | segment[3];
			break;
		case 1:
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


void writeLong(long i) {
	
	int pos = 4; // Start writing at the rightmost position on the LCD

	// Loop until the number is reduced to 0 or all positions are filled
	for (int count = 0; count < 5; count++) {
		if (i != 0) {
			int digit = i % 10; // Extract least significant digit
			writeChar(digit + '0', pos); // Convert to char and write to LCD
			i /= 10; // Remove the processed digit
			} else {
			writeChar(' ', pos); // Clear remaining positions if the number has fewer than 5 digits
		}
		pos--; // Move to the next LCD position to the left
	}
}


bool isPrime(int number)
{
	if (number <= 1) // 0 and 1 are not prime numbers
	{
		return false;
	}
	for (int i=2; i*i <= number; i++) //loop from 2 to sqrt(number)
	{
		if (number % i == 0) return false;	//divisible => not prime
	}
	//is prime if no factors
	return true;
}


void primes() {
	long i = 1;
	while (true) {
		if (isPrime(i)) 
		{
			writeLong(i);
			_delay_ms(5000);
		}
		i++;
	}
	
}


int main(void) {
	init();
	
	/*
	writeChar('8', 0);
	writeChar('0', 1);
	writeChar('0', 2);
	writeChar('8', 3);
	writeChar('5', 4);
	*/

	//writeLong(634517284);
	//writeLong(42);  
	
	//primes();     
}