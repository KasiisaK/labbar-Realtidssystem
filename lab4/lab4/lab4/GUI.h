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

// Public methods
void swithToLeftGen(GUI *self)
void swithToRightGen(GUI *self);
void adjustFrequency(GUI *self, int delta);
void saveRestore(GUI *self);
void updateDisplay(GUI *self);
void LCD_init(void);
void printAt(long num, int pos);

#endif