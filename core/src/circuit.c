#include <stddef.h>
#include "circuit.h"
#include "utils/string_utils.h"

void circuit_init(Circuit *circuit, const char *name)
{
    string_copy(circuit->name, MAX_NAME_LENGTH, name);

    circuit->gate_count = 0;
    circuit->gate_next_id = 0;
    circuit->connection_count = 0;
    circuit->connection_next_id = 0;
}

int circuit_add_gate(Circuit *circuit, GateType type)
{
    if (circuit == NULL) return -1;
    if (circuit->gate_count >= MAX_GATES) return -1;

    int id = circuit->gate_next_id;
    
    Gate *gate = &circuit->gates[id];

    gate->id = id;
    gate->type = type;
    gate->input_a = false;
    gate->input_b = false;
    gate->output  = false;
    
    circuit->gate_count++;
    circuit->gate_next_id++;

    return id;
}

int circuit_connect_gate(Circuit *circuit, int from_gate_id, int to_gate_id, GateInput to_input)
{
    if (circuit == NULL) return -1;

    Gate *from_gate_ptr = circuit_get_gate_by_id(circuit, from_gate_id);
    Gate *to_gate_ptr = circuit_get_gate_by_id(circuit, to_gate_id);

    if (from_gate_ptr == NULL) return -1;
    if (to_gate_ptr == NULL) return -1;
    if (circuit->connection_count >= MAX_CONNECTIONS) return -1;
    if (to_input < 0 || to_input >= INPUT_COUNT) return -1;
    if (to_gate_ptr->type == GATE_NOT && to_input == INPUT_B) return -1;

    for (int i = 0; i < circuit->connection_count; i++)
        if (circuit->connections[i].to_gate_id == to_gate_ptr->id && circuit->connections[i].to_input == to_input) return -1;

    int id = circuit->connection_next_id;

    Connection *connection = &circuit->connections[id];

    connection->id = id;
    connection->from_gate_id = from_gate_ptr->id;
    connection->to_gate_id = to_gate_ptr->id;
    connection->to_input = to_input;

    circuit->connection_count++;
    circuit->connection_next_id++;

    return id;
}

Gate *circuit_get_gate_by_id(Circuit *circuit, const int id)
{
    if (circuit == NULL) return NULL;
    if (id < 0) return NULL;

    for (int i = 0; i < circuit->gate_count; i++)
        if (circuit->gates[i].id == id) return &circuit->gates[i];
    
    return NULL;
}

const Gate *circuit_get_gate_by_id_const(const Circuit *circuit, const int id)
{
    if (circuit == NULL) return NULL;
    if (id < 0) return NULL;

    for (int i = 0; i < circuit->gate_count; i++)
        if (circuit->gates[i].id == id) return &circuit->gates[i];
    
    return NULL;
}