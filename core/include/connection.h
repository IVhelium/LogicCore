#pragma once
#include "../include/gate.h"

typedef struct
{
    int from_gate;
    int to_gate;
    GateInput to_input;
} Connection;
