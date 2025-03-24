#include "input_handler.h"

void getUserInput(Input_handler *self) {
    char input;
    scanf("%c", input);
    procesInput(self, input);
    getUserInput(self);
}

void procesInput(Input_handler *self, char input) {
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