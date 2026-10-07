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