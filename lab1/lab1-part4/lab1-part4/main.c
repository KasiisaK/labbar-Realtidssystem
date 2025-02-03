#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>

// Part 2
#define PRESCALER 256
#define F_CPU 8000000UL // 8 MHz CPU clock
#define TIMER_TICKS_PER_SECOND (F_CPU / PRESCALER)

// Part 3
#define LCD_SEGMENT1 0b00000001 //  segment 1
#define LCD_SEGMENT2 0b00100000 //  segment 2
uint8_t joystick_pressed = 0;

// Lookup table
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

//returns wall of data based on char input ('0' = 48 (char))
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

    // Configure bit 7 of PORTB as input and enable pull-up resistor
	DDRB &= ~(1 << PB7);
	PORTB |= (1 << PB7);
}

//write a char ch at position pos
void writeChar(char ch, uint8_t pos) {
	//check if outside range
	if (pos > 4 || pos < 0) return;	

	//get correct char data
	int* segment = getSegmentForChar(ch);
	
	//chose position
	switch (pos) {
		case 0:
			//segment start at 0, 5, 10, 15, higher 4 bits.
			//(LCDDR0 & 0xF0) clears the segment before writing 
			LCDDR0 = (LCDDR0 & 0xF0) | segment[0];
			LCDDR5 = (LCDDR5 & 0xF0) | segment[1];
			LCDDR10 = (LCDDR10 & 0xF0) | segment[2];
			LCDDR15 = (LCDDR15 & 0xF0) | segment[3];
			break;
		case 1:
			//same register different segments
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

//writes a number i to LCD
void writeLong(long i) {	
	int pos = 4; //start writing at the rightmost pos

	//loop 5 times
	for (int count = 0; count < 5; count++) {
		//stop if number is 0.
		if (i == 0) {
				return;
				//print LS number
			} else {
				//extract least significant digit and remove it from i
				int digit = i % 10;
				i /= 10;
				//'0' is 48 in ASCI and digit offsets to right ASCI char
				writeChar(digit + '0', pos);
		}
		pos--; //next pos
	}
}

bool isPrime(int number)
{
	//0 and 1 are not prime numbers
	if (number <= 1) return false; 

	//loop from 2 to sqrt(number)
	for (int i=2; i*i <= number; i++) 
	{
		if (number % i == 0) return false;	//divisible => not prime
	}
	//is prime if no factors
	return true;
}

//loop through numbers, and if it is prime print to LCD
void prime(long i) {
    if (isPrime(i)) 
    {
        writeLong(i);
        //_delay_ms(1000);
    }
}

//part 2
void busyWaitUntil(uint16_t target) {
	while (((int16_t)(TCNT1 - target)) < 0) {
	}
}

void blink() {
	uint16_t half_period = TIMER_TICKS_PER_SECOND / 2; // Half the period for 1 Hz blinking
	static uint16_t next_timer_value = 0;   // Set the initial target time

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

//part 3
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
	bool oldValue = joystick_pressed;          

	// Check if joystick is pressed (active low, bit 7 of PINB == 0)
	if (!(PINB & (1 << PB7))) {
		if (!joystick_pressed) {
			joystick_pressed = 1;
			// Checks toggle
			if (oldValue == 0 && joystick_pressed == 1) toggle_lcd(&current_segment);
		}
		} else {
		joystick_pressed = 0;
	}
}


int main(void) {
	init();
    long primeNumber = 1;
    while(1){
        prime(primeNumber);
		primeNumber++;
		
        blink();
        button();
	}
}