#include <stddef.h>
#include "circuit.h"

void circuit_init(Circuit *circuit, const char *name)
{
    #pragma region Name
    // Копируем строку в массив
    int i = 0;

    while (name[i] != '\0')
    {
        circuit->name[i] = name[i];
        i++;
    }
    
    // После выхода из цикла присаиваем последнему элементу специальный символ конца строки
    circuit->name[i] = '\0';
    #pragma endregion

    circuit->connection_count = 0;
    circuit->gate_count = 0;
}

int circuit_add_gate(Circuit *circuit, GateType type)
{
    if (circuit == NULL)
        return -1;

    if (circuit->gate_count >= MAX_GATES)
        return -1;

    int id = circuit->gate_count;
    
    Gate *gate = &circuit->gates[id];   // Присваиваем адрес конкретного Gate чтобы он сохранился в памяти

    gate->id = id;
    gate->type = type;
    gate->input_a = false;
    gate->input_b = false;
    gate->output  = false;
    
    circuit->gate_count++;

    return id;
}