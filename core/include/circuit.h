#pragma once

#include "gate.h"
#include "connection.h"

#define MAX_NAME_LENGTH 100
#define MAX_GATES 100
#define MAX_CONNECTIONS 300

typedef struct
{
    Connection connections[MAX_CONNECTIONS];
    Gate gates[MAX_GATES];
    char name[MAX_NAME_LENGTH];
    int gate_count;
    int gate_next_id;
    int connection_count;
    int connection_next_id;
} Circuit;


void circuit_init(Circuit *circuit, const char *name);

int circuit_add_gate(Circuit *circuit, GateType type);
int circuit_connect_gate(
    Circuit *circuit,
    int from_gate_id,
    int to_gate_id,
    GateInput to_input
);

Gate *circuit_get_gate_by_id(Circuit *circuit, const int id);
const Gate *circuit_get_gate_by_id_const(const Circuit *circuit, const int id);