#include "bridge.h"
#include <stdbool.h>

void switchLightState(Bridge *self) {
    self->northTraficLightOn = !self->northTraficLightOn;
}