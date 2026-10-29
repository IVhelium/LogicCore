#pragma once
#include "gate.h"

typedef struct
{
    int id;
    int from_gate_id;
    int to_gate_id;
    GateInput to_input;
} Connection;
