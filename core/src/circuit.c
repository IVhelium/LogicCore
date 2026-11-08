#include <stddef.h>
#include "circuit.h"
#include "utils/string_utils.h"

static int circuit_find_connection_index_by_id(const Circuit *circuit, int id);


static int circuit_find_connection_index_by_id(const Circuit *circuit, int id)
{
    if (circuit == NULL) return -1;
    if (id < 0) return -1;

    for (int i = 0; i < circuit->connection_count; i++)
        if (circuit->connections[i].id == id) return i;

    return -1;
}


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

    int index = circuit->gate_count;
    int id = circuit->gate_next_id;

    Gate *gate = &circuit->gates[index];

    gate->id = id;
    gate->type = type;
    for (int i = 0; i < INPUT_COUNT; i++) gate->inputs[i] = false;
    gate->output = false;
    
    circuit->gate_count++;
    circuit->gate_next_id++;

    return id;
}

int circuit_connect_gate(Circuit *circuit, int from_gate_id, int to_gate_id, GateInput to_input)
{
    if (circuit == NULL) return -1;

    Gate *from_gate = circuit_get_gate_by_id(circuit, from_gate_id);
    Gate *to_gate = circuit_get_gate_by_id(circuit, to_gate_id);

    if (from_gate == NULL) return -1;
    if (to_gate == NULL) return -1;
    if (circuit->connection_count >= MAX_CONNECTIONS) return -1;
    if (to_input < 0 || to_input >= INPUT_COUNT) return -1;
    if (to_gate->type == GATE_NOT && to_input == INPUT_B) return -1;

    for (int i = 0; i < circuit->connection_count; i++)
        if (circuit->connections[i].to_gate_id == to_gate->id && circuit->connections[i].to_input == to_input) return -1;

    int index = circuit->connection_count;
    int id = circuit->connection_next_id;

    Connection *connection = &circuit->connections[index];

    connection->id = id;
    connection->from_gate_id = from_gate->id;
    connection->to_gate_id = to_gate->id;
    connection->to_input = to_input;

    circuit->connection_count++;
    circuit->connection_next_id++;

    return id;
}


bool circuit_remove_connection(Circuit *circuit, int connection_id)
{
    if (circuit == NULL) return false;
    if (connection_id < 0) return false;

    int index = circuit_find_connection_index_by_id(circuit, connection_id);
    if (index == -1) return false;

    for (int i = index; i < circuit->connection_count - 1; i++)
        circuit->connections[i] = circuit->connections[i + 1];
    
    circuit->connection_count--;

    return true;
}


Gate *circuit_get_gate_by_id(Circuit *circuit, int id)
{
    if (circuit == NULL) return NULL;
    if (id < 0) return NULL;

    for (int i = 0; i < circuit->gate_count; i++)
        if (circuit->gates[i].id == id) return &circuit->gates[i];
    
    return NULL;
}

const Gate *circuit_get_gate_by_id_const(const Circuit *circuit, int id)
{
    if (circuit == NULL) return NULL;
    if (id < 0) return NULL;

    for (int i = 0; i < circuit->gate_count; i++)
        if (circuit->gates[i].id == id) return &circuit->gates[i];
    
    return NULL;
}