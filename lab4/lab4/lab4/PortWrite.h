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
#define initPortWrite() { initObject() }

// Function declarations
void setPin(PortWrite *self, int bit, int value);
void togglePin(PortWrite *self, int bit);

#endif
