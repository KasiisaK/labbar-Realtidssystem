#ifndef GUI_H
#define GUI_H

#include "TinyTimber.h"
#include "PulseGen.h"

typedef struct {
    Object super;
    PulseGen *gen1;
    PulseGen *gen2;
    int activeGen;  // 0 = gen1, 1 = gen2
    int savedFreq1;
    int savedFreq2;
} GUI;

#define initGUI(g1, g2) { initObject(), g1, g2, 0, 0, 0 }

// Public methods
void switchFocus(GUI *self, int newActive);
void adjustFrequency(GUI *self, int delta);
void saveRestore(GUI *self);
void updateDisplay(GUI *self);
void LCD_init(void);
void printAt(long num, int pos);
void updateDisplay(GUI *self);

#endif