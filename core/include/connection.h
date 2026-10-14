#pragma once
#include "gate.h"

typedef struct
{
    int id;
    int from_gate;
    int to_gate;
    GateInput to_input;
} Connection;
