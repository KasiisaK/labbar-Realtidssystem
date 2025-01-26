#include <avr/io.h>
// LCD digit mapping for "0"
const uint8_t digit_map[10] = {
	0b0111111, // '0'
	0b0000110, // '1'
	0b1011011, // '2'
	0b1001111, // '3'
	0b1100110, // '4'
	0b1101101, // '5'
	0b1111101, // '6'
	0b0000111, // '7'
	0b1111111, // '8'
	0b1101111  // '9'
};

void writeChar(uint8_t pos, uint8_t segment)
{
	if(pos > 5) return;
	
	switch (pos) {
		case 0:
		LCDDR0 = LCDDR0 | 0b00000001;
		LCDDR5 = LCDDR5 | 0b00000101;
		LCDDR10 = LCDDR10 | 0b00000101;
		LCDDR15 = LCDDR15 | 0b00000001;
		break;
		case 1:
		LCDDR0 = LCDDR0 | 0b00010000;
		LCDDR5 = LCDDR5 | 0b01010000;
		LCDDR10 = LCDDR10 | 0b01010000;
		LCDDR15 = LCDDR15 | 0b00010000;
		break;
		case 2:
		LCDDR1 = LCDDR1 | 0b00000001;
		LCDDR6 = LCDDR6 | 0b00000101;
		LCDDR11 = LCDDR11 | 0b00000101;
		LCDDR16 = LCDDR16 | 0b00000001;
		break;
		case 3:
		LCDDR1 = LCDDR1 | 0b00010000;
		LCDDR6 = LCDDR6 | 0b01010000;
		LCDDR11 = LCDDR11 | 0b01010000;
		LCDDR16 = LCDDR16 | 0b00010000;
		case 4:
		LCDDR2 = 0b0001;
		LCDDR7 = 0b0101;
		LCDDR12 = 0b0101;
		LCDDR17 = 0b0001;
		break;
	}
}

void init(){
	CLKPR = 0x80;
	CLKPR = 0x00;
	LCDCRB = (1<<LCDCS) | (1<<LCDMUX1) | (1<<LCDMUX0) | (1<<LCDPM2) | (1<<LCDPM1) | (1<<LCDPM0);
	LCDFRR = (1<<LCDCD2) | (1<<LCDCD1) | (1<<LCDCD0);
	LCDCCR = (1<<LCDDC1) | (1<<LCDCC3) | (1<<LCDCC2) | (1<<LCDCC1);
	TCCR1A = (1<<WGM13) | (1<<WGM12) | (1<<COM1A1) | (1<<COM1A0);
	LCDCRA = (1<<LCDEN) | (1<<LCDAB);
}

int main(void)
{
	init();
	for (uint8_t i = 0; i < 5; i++) {
		writeChar(i, 0);
	}
}