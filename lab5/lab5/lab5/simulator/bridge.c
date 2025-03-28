#include "bridge.h"
#include <stdbool.h>

bool getNorthLightStatus(Bridge *self) {
    return self->northTraficLightOn;
}

bool getSouthLightStatus(Bridge *self) {
    return self->southTraficLightOn;
}

void changeLightState(Bridge *self, unsigned char status) {
    self->northTraficLightOn = (status & (1 << 0)); // Bit 0 = North Green
    self->southTraficLightOn = (status & (1 << 2)); // Bit 2 = South Green
}