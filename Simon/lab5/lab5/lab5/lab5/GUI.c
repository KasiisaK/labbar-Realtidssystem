/*
 * GUI.c
 *
 * Created: 2022-03-08 14:58:17
 *  Author: simeng-0
 */ 

#include "GUI.h"

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
int all[] = {0b1111, 0b1111, 0b1111, 0b1111};
int none[] = {0b0000, 0b0000, 0b0000, 0b0000};


void writeChar(char ch, int pos){
	int bitshift, rbitshift;
	if(pos % 2 == 0){
		bitshift = 0;
		rbitshift = 4;
		}else{
		bitshift = 4;
		rbitshift = 0;
	}

	switch(pos){
		case 0: case 1:
		switch(ch){
			case '0':
			LCDDR0 = ((LCDDR0 & (0b1111<<rbitshift)) | zero[0]<<bitshift);
			LCDDR5 = (LCDDR5 & (0b11111<<rbitshift)) | zero[1]<<bitshift;
			LCDDR10= (LCDDR10 & (0b1111<<rbitshift)) | zero[2]<<bitshift;
			LCDDR15= (LCDDR15 & (0b1111<<rbitshift)) | zero[3]<<bitshift;
			break;
			case '1':
			LCDDR0 = ((LCDDR0 & (0b1111<<rbitshift))  | one[0]<<bitshift);
			LCDDR5 = (LCDDR5 & (0b1111<<rbitshift))  | one[1]<<bitshift;
			LCDDR10= (LCDDR10 & (0b1111<<rbitshift)) | one[2]<<bitshift;
			LCDDR15= (LCDDR15 & (0b1111<<rbitshift)) | one[3]<<bitshift;
			break;
			case '2':
			LCDDR0 = ((LCDDR0 & (0b1111<<rbitshift))  | two[0]<<bitshift);
			LCDDR5 = (LCDDR5 & (0b1111<<rbitshift))  | two[1]<<bitshift;
			LCDDR10= (LCDDR10 & (0b1111<<rbitshift)) | two[2]<<bitshift;
			LCDDR15= (LCDDR15 & (0b1111<<rbitshift)) | two[3]<<bitshift;
			break;
			case '3':
			LCDDR0 = ((LCDDR0 & (0b1111<<rbitshift))  | three[0]<<bitshift);
			LCDDR5 = (LCDDR5 & (0b1111<<rbitshift))  | three[1]<<bitshift;
			LCDDR10= (LCDDR10 & (0b1111<<rbitshift)) | three[2]<<bitshift;
			LCDDR15= (LCDDR15 & (0b1111<<rbitshift)) | three[3]<<bitshift;
			break;
			case '4':
			LCDDR0 = ((LCDDR0 & (0b1111<<rbitshift))  | four[0]<<bitshift);
			LCDDR5 = (LCDDR5 & (0b1111<<rbitshift))  | four[1]<<bitshift;
			LCDDR10= (LCDDR10 & (0b1111<<rbitshift)) | four[2]<<bitshift;
			LCDDR15= (LCDDR15 & (0b1111<<rbitshift)) | four[3]<<bitshift;
			break;
			case '5':
			LCDDR0 = ((LCDDR0 & (0b1111<<rbitshift))  | five[0]<<bitshift);
			LCDDR5 = (LCDDR5 & (0b1111<<rbitshift))  | five[1]<<bitshift;
			LCDDR10= (LCDDR10 & (0b1111<<rbitshift)) | five[2]<<bitshift;
			LCDDR15= (LCDDR15 & (0b1111<<rbitshift)) | five[3]<<bitshift;
			break;
			case '6':
			LCDDR0 = ((LCDDR0 & (0b1111<<rbitshift))  | six[0]<<bitshift);
			LCDDR5 = (LCDDR5 & (0b1111<<rbitshift))  | six[1]<<bitshift;
			LCDDR10= (LCDDR10 & (0b1111<<rbitshift)) | six[2]<<bitshift;
			LCDDR15= (LCDDR15 & (0b1111<<rbitshift)) | six[3]<<bitshift;
			break;
			case '7':
			LCDDR0 = ((LCDDR0 & (0b1111<<rbitshift))  | seven[0]<<bitshift);
			LCDDR5 = (LCDDR5 & (0b1111<<rbitshift))  | seven[1]<<bitshift;
			LCDDR10= (LCDDR10 & (0b1111<<rbitshift)) | seven[2]<<bitshift;
			LCDDR15= (LCDDR15 & (0b1111<<rbitshift)) | seven[3]<<bitshift;
			break;
			case '8':
			LCDDR0 = ((LCDDR0 & (0b1111<<rbitshift))  | eight[0]<<bitshift);
			LCDDR5 = (LCDDR5 & (0b1111<<rbitshift))  | eight[1]<<bitshift;
			LCDDR10= (LCDDR10 & (0b1111<<rbitshift)) | eight[2]<<bitshift;
			LCDDR15= (LCDDR15 & (0b1111<<rbitshift)) | eight[3]<<bitshift;
			break;
			case '9':
			LCDDR0 = ((LCDDR0 & (0b1111<<rbitshift))  | nine[0]<<bitshift);
			LCDDR5 = (LCDDR5 & (0b1111<<rbitshift))  | nine[1]<<bitshift;
			LCDDR10= (LCDDR10 & (0b1111<<rbitshift)) | nine[2]<<bitshift;
			LCDDR15= (LCDDR15 & (0b1111<<rbitshift)) | nine[3]<<bitshift;
			break;
			default:
			LCDDR0 = none[0]<<bitshift;
			LCDDR5 = none[1]<<bitshift;
			LCDDR10= none[2]<<bitshift;
			LCDDR15= none[3]<<bitshift;
			break;
		}
		break;
		case 2: case 3:
		switch(ch){
			case '0':
			LCDDR1 = (LCDDR1 & (0b1111<<rbitshift)) | zero[0]<<bitshift;
			LCDDR6 = (LCDDR6 & (0b1111<<rbitshift)) | zero[1]<<bitshift;
			LCDDR11= (LCDDR11 & (0b1111<<rbitshift)) | zero[2]<<bitshift;
			LCDDR16= (LCDDR16 & (0b1111<<rbitshift)) | zero[3]<<bitshift;
			break;
			case '1':
			LCDDR1 = (LCDDR1 & (0b1111<<rbitshift))  | one[0]<<bitshift;
			LCDDR6 = (LCDDR6 & (0b1111<<rbitshift))  | one[1]<<bitshift;
			LCDDR11= (LCDDR11 & (0b1111<<rbitshift)) | one[2]<<bitshift;
			LCDDR16= (LCDDR16 & (0b1111<<rbitshift)) | one[3]<<bitshift;
			break;
			case '2':
			LCDDR1 = (LCDDR1 & (0b1111<<rbitshift))  | two[0]<<bitshift;
			LCDDR6 = (LCDDR6 & (0b1111<<rbitshift))  | two[1]<<bitshift;
			LCDDR11= (LCDDR11 & (0b1111<<rbitshift)) | two[2]<<bitshift;
			LCDDR16= (LCDDR16 & (0b1111<<rbitshift)) | two[3]<<bitshift;
			break;
			case '3':
			LCDDR1 = (LCDDR1 & (0b1111<<rbitshift))  | three[0]<<bitshift;
			LCDDR6 = (LCDDR6 & (0b1111<<rbitshift))  | three[1]<<bitshift;
			LCDDR11= (LCDDR11 & (0b1111<<rbitshift)) | three[2]<<bitshift;
			LCDDR16= (LCDDR16 & (0b1111<<rbitshift)) | three[3]<<bitshift;
			break;
			case '4':
			LCDDR1 = (LCDDR1 & (0b1111<<rbitshift))  | four[0]<<bitshift;
			LCDDR6 = (LCDDR6 & (0b1111<<rbitshift))  | four[1]<<bitshift;
			LCDDR11= (LCDDR11 & (0b1111<<rbitshift)) | four[2]<<bitshift;
			LCDDR16= (LCDDR16 & (0b1111<<rbitshift)) | four[3]<<bitshift;
			break;
			case '5':
			LCDDR1 = (LCDDR1 & (0b1111<<rbitshift))  | five[0]<<bitshift;
			LCDDR6 = (LCDDR6 & (0b1111<<rbitshift))  | five[1]<<bitshift;
			LCDDR11= (LCDDR11 & (0b1111<<rbitshift)) | five[2]<<bitshift;
			LCDDR16= (LCDDR16 & (0b1111<<rbitshift)) | five[3]<<bitshift;
			break;
			case '6':
			LCDDR1 = (LCDDR1 & (0b1111<<rbitshift))  | six[0]<<bitshift;
			LCDDR6 = (LCDDR6 & (0b1111<<rbitshift))  | six[1]<<bitshift;
			LCDDR11= (LCDDR11 & (0b1111<<rbitshift)) | six[2]<<bitshift;
			LCDDR16= (LCDDR16 & (0b1111<<rbitshift)) | six[3]<<bitshift;
			break;
			case '7':
			LCDDR1 = (LCDDR1 & (0b1111<<rbitshift))  | seven[0]<<bitshift;
			LCDDR6 = (LCDDR6 & (0b1111<<rbitshift))  | seven[1]<<bitshift;
			LCDDR11= (LCDDR11 & (0b1111<<rbitshift)) | seven[2]<<bitshift;
			LCDDR16= (LCDDR16 & (0b1111<<rbitshift)) | seven[3]<<bitshift;
			break;
			case '8':
			LCDDR1 = (LCDDR1 & (0b1111<<rbitshift))  | eight[0]<<bitshift;
			LCDDR6 = (LCDDR6 & (0b1111<<rbitshift))  | eight[1]<<bitshift;
			LCDDR11= (LCDDR11 & (0b1111<<rbitshift)) | eight[2]<<bitshift;
			LCDDR16= (LCDDR16 & (0b1111<<rbitshift)) | eight[3]<<bitshift;
			break;
			case '9':
			LCDDR1 = (LCDDR1 & (0b1111<<rbitshift))  | nine[0]<<bitshift;
			LCDDR6 = (LCDDR6 & (0b1111<<rbitshift))  | nine[1]<<bitshift;
			LCDDR11= (LCDDR11 & (0b1111<<rbitshift)) | nine[2]<<bitshift;
			LCDDR16= (LCDDR16 & (0b1111<<rbitshift)) | nine[3]<<bitshift;
			break;
			default:
			LCDDR1 = none[0]<<bitshift;
			LCDDR6 = none[1]<<bitshift;
			LCDDR11= none[2]<<bitshift;
			LCDDR16= none[3]<<bitshift;
			break;
		}
		break;
		case 4: case 5:
		switch(ch){
			case '0':
			LCDDR2 = ((LCDDR2 & (0b1111<<rbitshift)) | zero[0]<<bitshift);
			LCDDR7 = (LCDDR7 & (0b1111<<rbitshift)) | zero[1]<<bitshift;
			LCDDR12= (LCDDR12 & (0b1111<<rbitshift)) | zero[2]<<bitshift;
			LCDDR17= (LCDDR17 & (0b1111<<rbitshift)) | zero[3]<<bitshift;
			break;
			case '1':
			LCDDR2 = ((LCDDR2 & (0b1111<<rbitshift))  | one[0]<<bitshift);
			LCDDR7 = (LCDDR7 & (0b1111<<rbitshift))  | one[1]<<bitshift;
			LCDDR12= (LCDDR12 & (0b1111<<rbitshift)) | one[2]<<bitshift;
			LCDDR17= (LCDDR17 & (0b1111<<rbitshift)) | one[3]<<bitshift;
			break;
			case '2':
			LCDDR2 = ((LCDDR2 & (0b1111<<rbitshift))  | two[0]<<bitshift);
			LCDDR7 = (LCDDR7 & (0b1111<<rbitshift))  | two[1]<<bitshift;
			LCDDR12= (LCDDR12 & (0b1111<<rbitshift)) | two[2]<<bitshift;
			LCDDR17= (LCDDR17 & (0b1111<<rbitshift)) | two[3]<<bitshift;
			break;
			case '3':
			LCDDR2 = ((LCDDR2 & (0b1111<<rbitshift))  | three[0]<<bitshift);
			LCDDR7 = (LCDDR7 & (0b1111<<rbitshift))  | three[1]<<bitshift;
			LCDDR12= (LCDDR12 & (0b1111<<rbitshift)) | three[2]<<bitshift;
			LCDDR17= (LCDDR17 & (0b1111<<rbitshift)) | three[3]<<bitshift;
			break;
			case '4':
			LCDDR2 = ((LCDDR2 & (0b1111<<rbitshift))  | four[0]<<bitshift);
			LCDDR7 = (LCDDR7 & (0b1111<<rbitshift))  | four[1]<<bitshift;
			LCDDR12= (LCDDR12 & (0b1111<<rbitshift)) | four[2]<<bitshift;
			LCDDR17= (LCDDR17 & (0b1111<<rbitshift)) | four[3]<<bitshift;
			break;
			case '5':
			LCDDR2 = ((LCDDR2 & (0b1111<<rbitshift))  | five[0]<<bitshift);
			LCDDR7 = (LCDDR7 & (0b1111<<rbitshift))  | five[1]<<bitshift;
			LCDDR12= (LCDDR12 & (0b1111<<rbitshift)) | five[2]<<bitshift;
			LCDDR17= (LCDDR17 & (0b1111<<rbitshift)) | five[3]<<bitshift;
			break;
			case '6':
			LCDDR2 = ((LCDDR2 & (0b1111<<rbitshift))  | six[0]<<bitshift);
			LCDDR7 = (LCDDR7 & (0b1111<<rbitshift))  | six[1]<<bitshift;
			LCDDR12= (LCDDR12 & (0b1111<<rbitshift)) | six[2]<<bitshift;
			LCDDR17= (LCDDR17 & (0b1111<<rbitshift)) | six[3]<<bitshift;
			break;
			case '7':
			LCDDR2 = ((LCDDR2 & (0b1111<<rbitshift))  | seven[0]<<bitshift);
			LCDDR7 = (LCDDR7 & (0b1111<<rbitshift))  | seven[1]<<bitshift;
			LCDDR12= (LCDDR12 & (0b1111<<rbitshift)) | seven[2]<<bitshift;
			LCDDR17= (LCDDR17 & (0b1111<<rbitshift)) | seven[3]<<bitshift;
			break;
			case '8':
			LCDDR2 = ((LCDDR2 & (0b1111<<rbitshift))  | eight[0]<<bitshift);
			LCDDR7 = (LCDDR7 & (0b1111<<rbitshift))  | eight[1]<<bitshift;
			LCDDR12= (LCDDR12 & (0b1111<<rbitshift)) | eight[2]<<bitshift;
			LCDDR17= (LCDDR17 & (0b1111<<rbitshift)) | eight[3]<<bitshift;
			break;
			case '9':
			LCDDR2 = ((LCDDR2 & (0b1111<<rbitshift))  | nine[0]<<bitshift);
			LCDDR7 = (LCDDR7 & (0b1111<<rbitshift))  | nine[1]<<bitshift;
			LCDDR12= (LCDDR12 & (0b1111<<rbitshift)) | nine[2]<<bitshift;
			LCDDR17= (LCDDR17 & (0b1111<<rbitshift)) | nine[3]<<bitshift;
			break;
			default:
			LCDDR2 = none[0]<<bitshift;
			LCDDR7 = none[1]<<bitshift;
			LCDDR12= none[2]<<bitshift;
			LCDDR17= none[3]<<bitshift;
			break;
		}
		break;
		default:	//reset display
		LCDDR0 = LCDDR0 & 0b01000100;
		LCDDR5 = LCDDR5 & none[1];
		LCDDR10= LCDDR10& none[2];
		LCDDR15= LCDDR15& none[3];
		LCDDR1 = LCDDR1 & none[0];
		LCDDR6 = LCDDR6 & none[1];
		LCDDR11= LCDDR11& none[2];
		LCDDR16= LCDDR16& none[3];
		LCDDR2 = LCDDR2 & none[0];
		LCDDR7 = LCDDR7 & none[1];
		LCDDR12= LCDDR12& none[2];
		LCDDR17= LCDDR17& none[3];
		//LCDDR0 = LCDDR0 & none[0]<<bitshift;
		LCDDR5 = LCDDR5 & none[1]<<bitshift;
		LCDDR10= LCDDR10& none[2]<<bitshift;
		LCDDR15= LCDDR15& none[3]<<bitshift;
		LCDDR1 = LCDDR1 & none[0]<<bitshift;
		LCDDR6 = LCDDR6 & none[1]<<bitshift;
		LCDDR11= LCDDR11& none[2]<<bitshift;
		LCDDR16= LCDDR16& none[3]<<bitshift;
		LCDDR2 = LCDDR2 & none[0]<<bitshift;
		LCDDR7 = LCDDR7 & none[1]<<bitshift;
		LCDDR12= LCDDR12& none[2]<<bitshift;
		LCDDR17= LCDDR17& none[3]<<bitshift;
	}
}


void printAt(unsigned int num, int pos) {
	writeChar((num % 100) / 10 + '0', pos);
	pos++;
	writeChar( num % 10 + '0', pos);
}

void update(GUI *self){
	printAt(SYNC(self->road, getNorthBound, 0), 0);
	printAt(SYNC(self->road, getOnBridge, 0), 2);
	printAt(SYNC(self->road, getSouthBound, 0), 4);
}