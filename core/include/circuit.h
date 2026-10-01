#pragma once

#include "gate.h"
#include "connection.h"

#define MAX_GATES 100
#define MAX_CONNECTIONS 300



typedef struct
{
    Gate gates[MAX_GATES];
    Connection connections[MAX_CONNECTIONS];
} Circuit;
