#include <avr/io.h>
#include <avr/interrupt.h>
#include "TinyTimber.h"
#include "gui.h"
#include "USART.h"
#include "backend.h"




int main() {
	cli();
	// Declare objects
	GUI gui = initGUI();
	Backend backend;
	USART usart = initUSART(&backend);
	
	LCD_init();	
	sei();
	
	return TINYTIMBER(&usart, usart_init, NULL);
}