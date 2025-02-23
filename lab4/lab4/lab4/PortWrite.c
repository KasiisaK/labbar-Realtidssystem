#include "PortWrite.h"

// Set a specific bit on Port E high or low
void setPin(PortWrite *self, int bit, int value) {
    if (value) {
        PORTE |= (1 << bit);   // Set bit high
    } else {
        PORTE &= ~(1 << bit);  // Set bit low
    }
}

// Toggle a specific bit on Port E
void togglePin(PortWrite *self, int bit) {
    PORTE ^= (1 << bit);   // Toggle the bit
}
