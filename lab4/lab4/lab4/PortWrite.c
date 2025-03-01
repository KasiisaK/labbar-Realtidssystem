#include "PortWrite.h"

// Set a specific bit on Port E high or low
void turnOfPin(PortWrite *self, uint8_t bit) {
    PORTE &= ~(1 << bit);
}

// Toggle a specific bit on Port E
void togglePin(PortWrite *self, int bit) {
    PORTE ^= (1 << bit);   // Toggle the bit
}
