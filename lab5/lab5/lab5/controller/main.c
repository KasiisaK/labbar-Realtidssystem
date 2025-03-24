#include <avr/io.h>
#include <avr/interrupt.h>
#include "TinyTimber.h"
#include "gui.h"
#include "USART.h"
#include "traffic_light.h"
#include "backend.h"

// Declare objects
GUI gui = initGUI(); 
Backend backend;
USART usart = initUSART(&backend);
TrafficLight trafficLight = initTrafficLight(&gui, &backend);

int main() {
	LCD_init();
	backend_init(&backend);
	usart_init(&usart);
	
	sei();
	
	TINYTIMBER(&trafficLight, start, NULL);
	TINYTIMBER(&usart, start, NULL);
	
	return 0;
}