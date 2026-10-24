#include <stdio.h>
#include "menu/menu.h"
#include "menu/gate_menu.h"
#include "menu/connection_menu.h"
#include "utils/pagination.h"

// Circuit
static void menu_create_circuit(void);
static void menu_circuit(Circuit *circuit);


void menu_init(void)
{
    bool running = true;

    while (running)
    {
        int choice;

        printf("\n1. Create Circuit\n");
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
    if (circuit == NULL) return;

    bool running = true;

    while (running)
    {
        int choice;

        printf("\n=== Circuit: %s ===\n", circuit->name);

        printf("1. Add Gate\n");
        printf("2. Connect Gates\n");
        printf("3. Delete Gate\n");
        printf("4. Set Gate Input\n");
        printf("5. Circuit Run\n");
        printf("6. Exit\n");

        printf("> ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                menu_add_gate(circuit);
                break;
            
            case 5:
                for (size_t i = 0; i < 50; i++)
                {
                    circuit_add_gate(circuit, GATE_AND);
                    circuit_add_gate(circuit, GATE_NOT);
                    circuit_connect_gate(circuit, i, i, INPUT_A);
                }

                menu_list_connections(circuit, 10);
                break;
            
            case 4:
                menu_connect_gate(circuit);
                break;

            case 6:
                running = false;
                break;

            case 7:
                for (size_t i = 0; i < 50; i++)
                {
                    circuit_add_gate(circuit, GATE_AND);
                    circuit_add_gate(circuit, GATE_NOT);
                }
                
                menu_list_gates(circuit, 10);
                break;

            default:
                printf("Invalid option\n");
                break;
        }
    }
}

#pragma endregion