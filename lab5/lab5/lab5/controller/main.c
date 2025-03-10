#include <avr/io.h>
#include "TinyTimber.h"
#include "traffic_light.h"

TrafficLight trafficLight = initTrafficLight();


void main() {
	TINYTIMBER(&trafficLight, start, 0);
	
	return 0;
}