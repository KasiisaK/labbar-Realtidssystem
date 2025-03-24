#ifndef BRIDGE_H
#define BRIDGE_H

#include <stdbool.h>

typedef struct {
    bool northTraficLightOn;
    bool southTraficLightOn;
} Bridge;

#define initBridge() \
    {false, false}


bool getNorthLightStatus(Bridge *self);
bool getSouthLightStatus(Bridge *self);

void changeLightState(Bridge *self, unsigned char status);

#endif