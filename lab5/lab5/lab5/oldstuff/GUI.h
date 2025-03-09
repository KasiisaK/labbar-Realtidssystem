#ifndef GUI_H
#define GUI_H

#include <stdbool.h>


typedef struct {
    
} GUI;

#define initGUI() { initObject(),  }

// Print stuff
void LCD_init();
int* getSegmentForChar(char ch);
void printAt(long num, int pos);
void updateDisplay(GUI *self, int activeGen);

#endif