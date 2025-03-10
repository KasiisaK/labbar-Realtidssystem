#include <avr/io.h>
#include "TinyTimber.h"
#include "TrafficLight.h"
#include "USART.h"
#include "GUI.h"

GUI gui = initGUI();
TrafficLight trafficLight = initTrafficLight(&gui);
USART usart = initUSART(&trafficLight);

void main() {
	LCD_init();
	
	TINYTIMBER(&trafficLight, start, 0);
	
	return 0;
}