#ifndef GUI_H
#define GUI_H

#include "TinyTimber.h"
#include "PulseGen.h"

typedef struct {
    Object super;
    PulseGen *gen1;
    PulseGen *gen2;
    PulseGen *activeGen; //g1 deafult
} GUI;

#define initGUI(g1, g2) { initObject(), g1, g2, g1 }

// print stuff
void LCD_init();
int* getSegmentForChar(char ch);
void printAt(long num, int pos);
void updateOneOrTwo(GUI *self);

//logich stuff
void swithToLeftGen(GUI *self);
void swithToRightGen(GUI *self);
void adjustFrequency(GUI *self, int delta);
void saveRestore(GUI *self);
void updateDisplay(GUI *self);

#endif