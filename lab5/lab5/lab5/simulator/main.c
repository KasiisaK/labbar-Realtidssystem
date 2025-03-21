#include <avr/io.h>
#include <pthread.h>

#include "TinyTimber.h"
#include "input_handler.h"
#include "bridge.h"
#include "simulation.h"

#define FOSC 1843200// Clock Speed
#define BAUD 9600
#define MYUBRR FOSC/16/BAUD-1

void sysInit(){
    // Clock Prescale Register "maximum speed"
	CLKPR = 0b10000000; // Clock Prescaler Change Enable
	CLKPR = 0b00000000; // Set 0 for sysclock
}

void USART_Init(unsigned int ubrr) {
    //Power Reduction Register
    PRR |= (0 << PRUSART0);

    // Set baud rate
    UBRRH0 = (unsigned char)(ubrr>>8);
    UBRRL0 = (unsigned char)ubrr;
    // Enable receiver and transmitter
    UCSR0B = (1<<RXEN0)|(1<<TXEN0);
    // Set frame format: 8data, 2stop bit
    UCSRnC = (0<<USBS0)|(3<<UCSZ00);
}


void main() {
    // Mutexs
    static pthread_mutex_t northCar = PTHREAD_MUTEX_INITIALIZER;
    static pthread_mutex_t southCar = PTHREAD_MUTEX_INITIALIZER;
    static pthread_mutex_t bridgeCar = PTHREAD_MUTEX_INITIALIZER;
    // Objects
    Bridge bridge = initBridge();
    Simulation simulation = initSimulation(&bridge, &northCar, &southCar, &bridgeCar);
    Input_handler inputHandler = initInput_handler(&simulation);

    sysInit();
    USART_Init(MYUBRR);

    pthread_t inputThread;
    pthread_t simulationThread;

    pthread_create(inputThread, NULL, getUserInput, NULL);
    pthread_create(simulationThread, NULL, mainSimulationLoop, NULL);

}