#ifndef GUI_H
#define GUI_H

#include "TinyTimber.h"

typedef struct {
    Object super;
} GUI;

#define initGUI() { initObject()}

// print stuff
void LCD_init();
int* getSegmentForChar(char ch);
void printAt(long num, int pos);
void activeGenIndicator(PulseGen *activeGen, PulseGen *gen1);
void updateDisplay(GUI *gui, PulseGen *activeGen, PulseGen *gen1);

#endif