#ifndef GUI_H
#define GUI_H

#include "TinyTimber.h"

// GUI object
typedef struct {
    Object super;
    int selectedGen; // selectedGen=0 => gen 1, selectedGen=1 => gen 2
    int freq1;       // Frequency gen 1
    int freq2;       // Frequency gen 2
} GUI;

// Initialize a GUI object
#define initGUI() { initObject(), 0, 0, 0 }

// Function declarations
void updateDisplay(GUI *self, int unused);
void handleJoystick(GUI *self, int direction);

#endif
