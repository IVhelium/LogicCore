#include <stddef.h>
#include "gate.h"

static const char *gate_type_names[GATE_TYPE_COUNT] =
{
    [GATE_AND] = "AND",
    [GATE_NOT] = "NOT",
    [GATE_OR] =  "OR",
    [GATE_XOR] = "XOR"
};


void gate_update(Gate *gate)
{
    bool input_A = gate->input_a;
    bool input_B = gate->input_b;

    switch (gate->type)
    {
        case GATE_AND:
            gate->output = input_A & input_B;
            break;
        
        case GATE_NOT:
            gate->output = input_A ^ 1;   // Работает как инвертор. Когда на входе 0 инвертируется в 1
            break;
        
        case GATE_OR:
            gate->output = input_A | input_B;
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
    if (gate->type == GATE_NOT && input == INPUT_B)
        return;

    switch (input)
    {
        case INPUT_A:
            gate->input_a = value;
            break;
        
        case INPUT_B:
            gate->input_b = value;
            break;

        default:
            break;
    }
}

const char *gate_type_to_string(GateType type)
{
    if (type < 0 || type == GATE_TYPE_COUNT) return "UNKNOWN TYPE";
    if (gate_type_names[type] == NULL) return "UNKNOWN TYPE";

    return gate_type_names[type];
}