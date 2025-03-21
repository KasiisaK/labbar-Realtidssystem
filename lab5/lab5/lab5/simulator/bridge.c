#include "bridge.h"
#include <stdbool.h>

bool getLightState(Bridge *self) {
    return self->northTraficLightOn;
}

void changeLightState(Bridge *self) {
    __int8 status; //temp

    // Bit 0: Northbound green light status
    if (status & (1 << 0)) {
        // Northbound green
    }
    
    // Bit 1: Northbound red light status
    if (status & (1 << 1)) {
        // Northbound red
    }
    
    // Bit 2: Southbound green light status
    if (status & (1 << 2)) {
        // Southbound green
    }
    
    // Bit 3: Southbound red light status
    if (status & (1 << 3)) {
        // Southbound red
    }
}