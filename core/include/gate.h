#pragma once

typedef enum
{
    GATE_AND,
    GATE_NOT,
    GATE_OR,
    GATE_XOR,
    GATE_TYPE_COUNT
} GateType;

typedef enum
{
    INPUT_A,
    INPUT_B,
    INPUT_COUNT
} GateInput;

typedef struct
{
    int id;
    GateType type;    

    bool input_a;  // Указывает на значение предыдущего выхода
    bool input_b;
    bool output;
} Gate;


void gate_update(Gate *gate);

void gate_set_input(
    Gate *gate, 
    GateInput input, 
    bool value
);

const char *gate_type_to_string(GateType type);