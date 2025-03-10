#ifndef GUI_H
#define GUI_H

typedef struct {
	Object super;
} GUI;

void LCD_init();
void printAt(long num, int pos);
void writeChar(char ch, uint8_t pos);

#define initGUI() { initObject() }

#endif