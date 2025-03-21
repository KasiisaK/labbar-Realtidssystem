#include <stdbool.h>
#include <pthread.h>

// To simplify the logich asume that if the north light is one south is of and vise versa
// means only one light is need if dealy is added in the logic later

typedef struct {
    bool northTraficLightOn;
    bool southTraficLightOn;
} Bridge;

#define initBridge() \
    {true, false}


bool getNorthLightStatus(Bridge *self);
bool getSouthLightStatus(Bridge *self);

void changeLightState(Bridge *self);