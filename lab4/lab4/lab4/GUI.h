#ifndef GUI_H
#define GUI_H

#include "TinyTimber.h"

// GUI object
typedef struct {
    Object super;
} GUI;

// Initialize a GUI object
#define initGUI() { initObject(), 0, 0, 0 }

// Function declarations
void updateDisplay(GUI *self, int unused);
void LCD_init(GUI *self);

#endif