#ifndef PORTWRITE_H
#define PORTWRITE_H

#include <avr/io.h>
#include "TinyTimber.h"
#include <stdbool.h>

// Define PortWrite object
typedef struct {
    Object super;
} PortWrite;

// Initialization macro
#define initPortWrite() { initObject()}

// Function declarations
void turnOffPin(PortWrite *self, uint8_t bit);
void togglePin(PortWrite *self, uint8_t bit);

#endif
