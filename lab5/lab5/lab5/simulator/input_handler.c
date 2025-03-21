#include "input_handler.h"

void getUserInput(Input_handler *self) {
    scanf("%c", &(self->input));
    procesInput(self, self->input);
    AFTER(MSEC(50), self, getUserInput, NULL);
}

void procesInput(Input_handler *self, char input) {
    switch (input)
    {
    // Enqueues a new car in northbound direction
    case 'n':
        ASYNC(self->simObject, addCarNorth, NULL);
        break;
    // Enqueues a new car in southbound direction
    case 's':
		ASYNC(self->simObject, addCarSouth, NULL);
        break;
    // Exits the simulator
    case 'e':
        exit(0);
        break;
    default:
        break;
    }
}