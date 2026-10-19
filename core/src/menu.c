#include <stdio.h>
#include "menu.h"
#include "utils/string_utils.h"

// Circuit
static void menu_create_circuit(void);
static void menu_circuit(Circuit *circuit);

// Gate
static void menu_add_gate(Circuit *circuit);

// List
static void menu_list_gates(const Circuit *circuit, const int page_size);
static void menu_list_connections(const Circuit *circuit);


void menu_init(void)
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
        printf("7. List Gates\n");

        printf("> ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 1:
                menu_add_gate(circuit);
                break;
            
            case 5:
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


#pragma region Gate

static void menu_add_gate(Circuit *circuit)
{
    if (circuit == NULL) return;

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


#pragma region List

static void menu_list_gates(const Circuit *circuit, const int page_size)
{
    if (circuit == NULL) return;
    if (page_size <= 0) return;

    int page = 0;
    int total_pages = (circuit->gate_count + page_size - 1) / page_size;
    bool running = true;

    while (running)
    {
        int start = page * page_size;
        int end = start + page_size;

        if (end > circuit->gate_count) end = circuit->gate_count;

        printf("\nGate list: \n");
        printf("%-20s", "ID");
        printf("%-15s", "NAME");
        printf("%-15s", "INPUT A");
        printf("INPUT B\n");

        for (int i = start; i < end; i++)
        {
            printf("%-20d", circuit->gates[i].id);
            printf("%-17s", gate_type_to_string(circuit->gates[i].type));
            printf("%-15d", circuit->gates[i].input_a);

            // Если тип гейта NOT то в колонке INPUT B ставим "-", если нет показываем значение инпута
            if (circuit->gates[i].type == GATE_NOT)
                printf("%s\n", "-");
            else
                printf("%d\n", circuit->gates[i].input_b);
        }

        printf("___________________________________________________________\n");
        printf("Page: %d/%d\n\n", page + 1, total_pages);
        if (page + 1 < total_pages) printf("[N] - Next\n");
        if (page > 0) printf("[P] - Previous\n");
        printf("[Q] - Back\n\n");

        char input;
        printf("> ");
        scanf(" %c", &input);

        switch (input)
        {
            case 'N':
            case 'n':
                if (page + 1 < total_pages) page++;
                break;

            case 'P':
            case 'p':
                if (page > 0) page--;
                break;

            case 'Q':
            case 'q':
                running = false;
                break;

            default:
                break;
        }
    }
}

static void menu_list_connections(const Circuit *circuit)
{
    if (circuit == NULL) return;

    printf("Connection list: \n");
    printf("%-20s", "ID");
    printf("%-30s", "FROM");
    printf("%-30s", "TO");
    printf("TO INPUT\n");

    for (int i = 0; i < circuit->connection_count; i++)
    {
        char from_gate_text[32];
        char to_gate_text[32];

        const Connection *connection = &circuit->connections[i];

        printf("%-20d", connection->id);
        
        string_concat(from_gate_text, sizeof(from_gate_text), "(", gate_type_to_string(circuit->gates[connection->from_gate].type), ")");
        printf("%-7s%-23d", from_gate_text, connection->from_gate);

        string_concat(to_gate_text, sizeof(to_gate_text), "(", gate_type_to_string(circuit->gates[connection->to_gate].type), ")");
        printf("%-7s%-26d", to_gate_text, connection->to_gate);

        printf("%s\n", gate_input_to_string(connection->to_input));
    }
}

#pragma endregion