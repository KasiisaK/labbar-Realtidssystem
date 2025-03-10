#include "TinyTimber.h"
#include <stdbool.h>

// To simplify the logich asume that if the north light is one south is of and vise versa
// means only one light is need if dealy is added in the logic later

typedef struct {
    Object super;
    bool northTraficLightOn;
} Bridge;

#define initBridge() \
    {initObject(), true}


void switchLightState(Bridge *self);