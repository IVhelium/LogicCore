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

int circuit_connect_gate(Circuit *circuit, int from_gate, int to_gate, GateInput to_input)
{
    /*
        INPUT:
        circuit
        from_gate -> из какого Гейта идет сигнал
        to_gate -> к какому гейту подключаемся
        to_input -> к какому инпуту подключаемся

        CHECK:
        существует ли circuit?
        есть ли место в circuit для конекта?
        существует ли from_gate?
        существует ли to_gate?
        допустим ли такой инпут для выбраного Gate?

        ACTION:
        создать новый Connection

        RESULT:
        connection_count + 1

        RETURN:
        При успешном соединении вернуть id созданного коннекта
        При ошибке вернуть -1;
    */

    if (circuit == NULL) return -1;
    if (from_gate >= circuit->gate_count || from_gate < 0) return -1;
    if (to_gate >= circuit->gate_count || to_gate < 0) return -1;
    if (circuit->connection_count >= MAX_CONNECTIONS) return -1;
    if (to_input < 0 || to_input >= INPUT_COUNT) return -1;
    if (circuit->gates[to_gate].type == GATE_NOT && to_input == INPUT_B) return -1;

    for (int i = 0; i < circuit->connection_count; i++)
    {
        if (circuit->connections[i].to_gate == to_gate && circuit->connections[i].to_input == to_input) return -1;
    }

    int id = circuit->connection_count;

    Connection *connection = &circuit->connections[id];

    connection->from_gate = from_gate;
    connection->to_gate = to_gate;
    connection->to_input = to_input;

    circuit->connection_count++;

    return id;
}