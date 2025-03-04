#ifndef GUI_H
#define GUI_H

#include <stdbool.h>
#include "TinyTimber.h"
#include "PulseGen.h"

typedef struct {
    Object super;
	bool leftActive;
	PulseGen *gen1;
	PulseGen *gen2;
} GUI;

#define initGUI(gen1, gen2, status) { initObject(), status, gen1, gen2 }

// print stuff
void LCD_init();
int* getSegmentForChar(char ch);
void printAt(long num, int pos);
void activeGenIndicator(GUI *self, int activeGen);
void updateDisplay(GUI *self, int activeGen);
void setActive(GUI *self, bool status);

#endif