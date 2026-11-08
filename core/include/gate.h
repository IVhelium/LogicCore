#pragma once

typedef enum GateType
{
    GATE_AND,
    GATE_NOT,
    GATE_OR,
    GATE_XOR,
    GATE_TYPE_COUNT
} GateType;

typedef enum GateInput
{
    INPUT_A,
    INPUT_B,
    INPUT_COUNT
} GateInput;

typedef struct Gate
{
    int id;
    GateType type;    
    bool inputs[INPUT_COUNT];
    bool output;
} Gate;


void gate_update(Gate *gate);
void gate_set_input(
    Gate *gate, 
    GateInput input, 
    bool value
);

const char *gate_type_to_string(GateType type);
const char *gate_input_to_string(GateInput input);