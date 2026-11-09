#include <stddef.h>
#include "gate.h"

static const char *gate_type_names[GATE_TYPE_COUNT] =
{
    [GATE_AND] = "AND",
    [GATE_NOT] = "NOT",
    [GATE_OR]  = "OR",
    [GATE_XOR] = "XOR"
};

static const char *gate_input_names[INPUT_COUNT] =
{
    [INPUT_A] = "A",
    [INPUT_B] = "B"
};

void gate_update(Gate *gate)
{
    if (gate == NULL) return;

    bool input_A = gate->inputs[INPUT_A];
    bool input_B = gate->inputs[INPUT_B];

    switch (gate->type)
    {
        case GATE_AND:
            gate->output = input_A && input_B;
            break;
        
        case GATE_NOT:
            gate->output = !input_A;
            break;
        
        case GATE_OR:
            gate->output = input_A || input_B;
            break;
        
        case GATE_XOR:
            gate->output = input_A ^ input_B;
            break;

        default:
            break;
    }
}

void gate_set_input(Gate *gate, GateInput input, bool value)
{
    if (gate == NULL) return;
    if (input < 0 || input >= INPUT_COUNT) return;
    if (gate->type == GATE_NOT && input != INPUT_A) return;

    gate->inputs[input] = value;
}

const char *gate_type_to_string(GateType type)
{
    if (type < 0 || type >= GATE_TYPE_COUNT) return "UNKNOWN TYPE";
    if (gate_type_names[type] == NULL) return "UNKNOWN TYPE";

    return gate_type_names[type];
}

const char *gate_input_to_string(GateInput input)
{
    if (input < 0 || input >= INPUT_COUNT) return "UNKNOWN INPUT";
    if (gate_input_names[input] == NULL) return "UNKNOWN INPUT";

    return gate_input_names[input];
}