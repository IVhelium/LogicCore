#pragma once

typedef enum
{
    GATE_AND,
    GATE_NOT,
    GATE_OR,
    GATE_XOR
} GateType;

typedef struct
{
    int id;
    GateType type;    

    bool inputA;
    bool inputB;
    bool output;
} Gate;
