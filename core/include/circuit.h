#pragma once

#include "gate.h"
#include "connection.h"

#define MAX_NAME_LENGTH 100
#define MAX_GATES 100
#define MAX_CONNECTIONS 300

typedef struct
{
    char name[MAX_NAME_LENGTH];

    Gate gates[MAX_GATES];
    int gate_count;
    
    Connection connections[MAX_CONNECTIONS];
    int connection_count;
} Circuit;


void circuit_init(
    Circuit *circuit, 
    const char *name
);

int circuit_add_gate(
    Circuit *circuit, 
    GateType type
);

int circuit_connect_gate(
    Circuit *circuit,
    int from_gate,
    int to_gate,
    GateInput to_input
);