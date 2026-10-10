#include <stdio.h>
#include "menu.h"

// Circuit
static void menu_create_circuit(void);
static void menu_circuit(Circuit *circuit);

// Gate
static void menu_add_gate(Circuit *circuit);


void menu_init()
{
    bool running = true;

    while (running)
    {
        int choice;

        printf("1. Create Circuit\n");
        printf("2. Open circuit\n");
        printf("3. Exit\n");

        printf("> ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                menu_create_circuit();
                break;

            case 3:
                running = false;
                break;

            default:
                printf("Invalid option\n");
                break;
        }
    }
}

#pragma region Circuit

static void menu_create_circuit(void)
{
    // Ввод имени и инициализация схемы
    char name[MAX_NAME_LENGTH];

    printf("Insert name of the circuit: ");
    scanf("%s", name);

    Circuit circuit;

    circuit_init(&circuit, name);
    menu_circuit(&circuit);
}

static void menu_circuit(Circuit *circuit)
{
    bool running = true;

    while (running)
    {
        int choice;

        printf("\n=== Circuit: %s ===\n", circuit->name);

        printf("1. Add Gate\n");
        printf("2. Connect Gates\n");
        printf("3. Delete Gate\n");
        printf("4. Circuit Run\n");
        printf("5. Exit\n");

        printf("> ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                menu_add_gate(circuit);
                break;

            case 5:
                running = false;
                break;

            default:
                printf("Invalid option\n");
                break;
        }
    }
}

#pragma endregion

#pragma region Gate

static void menu_add_gate(Circuit *circuit)
{
    int choice;
    GateType type;

    printf("\n=== Choice a gate type ===\n");
    printf("1. AND\n");
    printf("2. NOT\n");
    printf("3. OR\n");
    printf("4. XOR\n");

    printf("> ");
    scanf("%d", &choice);

    switch (choice)
    {
        case 1:
            type = GATE_AND;
            break;
        
        case 2:
            type = GATE_NOT;
            break; 
        
        case 3:
            type = GATE_OR;
            break;
        
        case 4:
            type = GATE_XOR;
            break;

        default:
            printf("Invalid option\n");
            break;
    }

    int gate_id = circuit_add_gate(circuit, type);

    if (gate_id == -1)
    {
        printf("Failed to add Gate\n");
        return;
    }

    printf("Gate created. ID: %d\n", gate_id);
}

#pragma endregion