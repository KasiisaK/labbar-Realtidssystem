#include "bridge.h"
#include <stdbool.h>

bool getNorthLightStatus(Bridge *self) {
    return self->northTraficLightOn;
}

bool getSouthLightStatus(Bridge *self) {
    return self->southTraficLightOn;
}

void changeLightState(Bridge *self) {
    __int8 status; //temp

    // Bit 0: Northbound green light status
    if (status & (1 << 0)) {
        self->northTraficLightOn = true;
    }
    
    // Bit 1: Northbound red light status
    if (status & (1 << 1)) {
        self->northTraficLightOn = false;
    }
    
    // Bit 2: Southbound green light status
    if (status & (1 << 2)) {
        self->southTraficLightOn = true;
    }
    
    // Bit 3: Southbound red light status
    if (status & (1 << 3)) {
        self->southTraficLightOn = false;
    }
}