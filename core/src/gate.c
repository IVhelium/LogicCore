#include "gate.h"
#include <stddef.h>

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
    }
}