#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include <util/delay.h>

#include "GUI.h"
#include "PulseGenerator.h"
#include "TinyTimber.h"

//returns wall of data based on char input ('0' = 48 (char))
int* getSegmentForChar(char ch) {
    //LUT
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

//write a char ch at position pos
void writeChar(char ch, uint8_t pos) {
	//check if outside range
	if (pos > 4 || pos < 0) return;	

	//get correct char data
	int* segment = getSegmentForChar(ch);
	
	//chose position
	switch (pos) {
		case 0:
			//segment start att 0, 5, 10, 15, higher 4 bits.
			//(LCDDR0 & 0xF0) clears the segment before writing 
			LCDDR0 = (LCDDR0 & 0xF0) | segment[0];
			LCDDR5 = (LCDDR5 & 0xF0) | segment[1];
			LCDDR10 = (LCDDR10 & 0xF0) | segment[2];
			LCDDR15 = (LCDDR15 & 0xF0) | segment[3];
			break;
		case 1:
			//same segment just lower 4 bits
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

void printAt(long num, int pos) {
	writeChar((num % 100) / 10 + '0', pos);
	pos++;
	writeChar(num % 10 + '0', pos);
}

//write a number to the LCD
void updateDisplay(GUI *self) {
    printAt(self->freq1, 0); //gen1 hz at pos 0-1
    printAt(self->freq2, 3); //gen2 hz at pos 3-4
}

//joystick input
void handleJoystick(GUI *self, int direction) {
    if (direction == 1) {  //joystick up => inc frequency
        if (self->selectedGen == 0) self->freq1++;
        else self->freq2++;
    } else if (direction == -1) {  //joystick down => dec frequency
        if (self->selectedGen == 0 && self->freq1 > 0) self->freq1--;
        else if (self->selectedGen == 1 && self->freq2 > 0) self->freq2--;
    } else if (direction == 2) {  //joystick right => select gen 2
        self->selectedGen = 1;
    } else if (direction == -2) { //joystick right => select gen 1
        self->selectedGen = 0;
    }

    //update LCD
    ASYNC(self, updateDisplay);
}