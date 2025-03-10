#include "input_handler.h"

void getUserInput(Input_handler *self) {
    scanf("%c", &(self->input));
    procesInput(self, self->input);
}

void procesInput(Input_handler *self, char input) {
    switch (input)
    {
    // Enqueues a new car in northbound direction
    case 'n':
        /* code */
        break;
    // Enqueues a new car in southbound direction
    case 's':
        /* code */
        break;
    // Exits the simulator
    case 'e':
        /* code */
        break;
    default:
        break;
    }
}