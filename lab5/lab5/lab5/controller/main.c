#include <avr/io.h>
#include <avr/interrupt.h>
#include "TinyTimber.h"
#include "GUI.h"
#include "USART.h"
#include "traffic_light.h" // ADD THIS LINE

// Declare objects AFTER including headers
GUI gui = initGUI();
USART usart = initUSART(NULL); // Placeholder (fixed later)
TrafficLight trafficLight = initTrafficLight(&gui, &usart);

// Reassign usart with TrafficLight reference
trafficLight.usart = &usart; // Now usart has the correct reference

int main() {
	LCD_init();
	usart_init(&usart);
	
	sei();
	
	TINYTIMBER(&trafficLight, start, NULL);
	TINYTIMBER(&usart, start, NULL);
	return 0;
}