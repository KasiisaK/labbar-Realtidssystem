#include "bridge.h"
#include <stdbool.h>

bool getLightState(Bridge *self) {
    return self->northTraficLightOn;
}

void changeLightState(Bridge *self) {
    // Code
}