#include "userInput.h"
#include <unistd.h> // usleep()
#include <stdio.h>   // For scanf/printf
#include <stdlib.h>  // For exit

void* getUserInput(void* arg) {
    Input* self = (Input*)arg;
    while (1) {
        char input;
        scanf(" %c", &input); // Space skips whitespace
        procesInput(self, input);
        usleep(1000);
    }
    return NULL;
}

void procesInput(Input *self, char input) {
    switch (input)
    {
    // Enqueues a new car in northbound direction
    case 'n':
        addCarNorth(self->simObject);
        break;
    // Enqueues a new car in southbound direction
    case 's':
		addCarSouth(self->simObject);
        break;
    // Exits the simulator
    case 'e':
        exit(0);
        break;
    default:
        break;
    }
}