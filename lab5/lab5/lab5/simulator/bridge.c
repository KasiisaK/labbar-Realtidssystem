#include "bridge.h"
#include <stdbool.h>

bool getNorthLightStatus(Bridge *self) {
    return self->northTraficLightOn;
}

bool getSouthLightStatus(Bridge *self) {
    return self->southTraficLightOn;
}

void changeLightState(Bridge *self, unsigned char status) {

    // Bit 0: Northbound green light status
    if (status & 0b1000) {
        self->northTraficLightOn = true;
    }
    
    // Bit 1: Northbound red light status
    if (status & 0b0100) {
        self->northTraficLightOn = false;
    }
    
    // Bit 2: Southbound green light status
    if (status & 0b0010) {
        self->southTraficLightOn = true;
    }
    
    // Bit 3: Southbound red light status
    if (status & 0b0001) {
        self->southTraficLightOn = false;
    }
}