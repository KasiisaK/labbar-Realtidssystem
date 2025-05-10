#ifndef GUI_H
#define GUI_H

#include <avr/io.h>
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <stdbool.h>
#include "TinyTimber.h"

typedef struct {
	Object super;  // Inherit TinyTimber Object (for reactive integration)
} GUI;

// Initialize the LCD hardware
void LCD_init();

// Write a character to a specific LCD position
void writeChar(char ch, uint8_t pos);

// Display a 2-digit number at a specified position
void printAt(long num, int pos);

void LightIndicator(char northOrSouth, int offOrOn);

// GUI constructor macro
#define initGUI() { initObject() }

#endif