#pragma once

typedef enum
{
    GATE_AND,
    GATE_NOT,
    GATE_OR,
    GATE_XOR
} GateType;

typedef enum
{
    INPUT_A,
    INPUT_B
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
void gate_set_input(Gate *gate, GateInput input, bool value);