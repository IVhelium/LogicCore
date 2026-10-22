#include <stdio.h>
#include "menu.h"
#include "utils/string_utils.h"
#include "utils/pagination.h"

// Circuit
static void menu_create_circuit(void);
static void menu_circuit(Circuit *circuit);

// Gate
static void menu_add_gate(Circuit *circuit);
static void menu_connect_gate(Circuit *circuit);

// List
static void menu_list_gates(const Circuit *circuit, const int page_size);
static int menu_select_gate(const Circuit *circuit, const int page_size); 
static void menu_list_connections(const Circuit *circuit, const int page_size);


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

static void menu_connect_gate(Circuit *circuit)
{
    GateInput gate_input;
    int input;

    printf("Select from gate: ");
    int from_gate = menu_select_gate(circuit, 15);
    if (from_gate == -1) return;

    printf("Select to gate: ");
    int to_gate = menu_select_gate(circuit, 15);
    if (to_gate == -1) return;

    printf("1. INPUT A\n");
    printf("2. INPUT B\n");
    printf("Select input: ");
    scanf("%d", &input);

    switch (input)
    {
        case 1:
            gate_input = INPUT_A;
            break;
        
        case 2:
            gate_input = INPUT_B;
            break;

        default:
            break;
    }

    int connection = circuit_connect_gate(circuit, from_gate, to_gate, gate_input);

    printf("Connection created: %d", connection);
}

#pragma endregion


#pragma region List

static void menu_list_gates(const Circuit *circuit, const int page_size)
{
    if (circuit == NULL) return;
    if (page_size <= 0) return;

    bool running = true;

    Pagination pagination;
    if (!pagination_create(&pagination, 0, page_size, circuit->gate_count)) return;

    while (running)
    {
        printf("\nGate list: \n");
        printf("%-20s", "ID");
        printf("%-15s", "NAME");
        printf("%-15s", "INPUT A");
        printf("INPUT B\n");

        for (int i = pagination.start; i < pagination.end; i++)
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
        printf("Page: %d/%d\n\n", pagination.page + 1, pagination.total_pages);
        if (pagination.page + 1 < pagination.total_pages) printf("[N] - Next\n");
        if (pagination.page > 0) printf("[P] - Previous\n");
        printf("[Q] - Back\n\n");

        char input;
        printf("> ");
        scanf(" %c", &input);

        switch (input)
        {
            case 'N':
            case 'n':
                pagination_next(&pagination);
                break;

            case 'P':
            case 'p':
                pagination_previous(&pagination);
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

static int menu_select_gate(const Circuit *circuit, const int page_size)
{
    if (circuit == NULL) return -1;
    if (page_size <= 0) return -1;

    Pagination pagination;
    if (!pagination_create(&pagination, 0, page_size, circuit->gate_count)) return -1;

    while (1)
    {
        printf("\nGate list: \n");
        printf("%-20s", "ID");
        printf("%-15s", "NAME");
        printf("%-15s", "INPUT A");
        printf("INPUT B\n");

        for (int i = pagination.start; i < pagination.end; i++)
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
        printf("Page: %d/%d\n\n", pagination.page + 1, pagination.total_pages);
        if (pagination.page + 1 < pagination.total_pages) printf("[N] - Next\n");
        if (pagination.page > 0) printf("[P] - Previous\n");
        printf("[Q] - Back\n");
        printf("[ID] - Select Gate\n\n");

        char input[32];
        printf("> ");
        scanf("%31s", input);

        if ((input[0] == 'N' && input[1] == '\0') || (input[0] == 'n' && input[1] == '\0'))
            pagination_next(&pagination);
        else if ((input[0] == 'P' && input[1] == '\0') || (input[0] == 'p' && input[1] == '\0'))
            pagination_previous(&pagination);
        else if ((input[0] == 'Q' && input[1] == '\0') || (input[0] == 'q' && input[1] == '\0'))
            return -1;
        else if ((input[0] == 'I' && input[1] == 'D' && input[2] == '\0') || (input[0] == 'i' && input[1] == 'd' && input[2] == '\0'))
        {
            int id;
            printf("Choose gate id: ");
            scanf("%d", &id);

            for (int i = 0; i < circuit->gate_count; i++)
                if (circuit->gates[i].id == id) return circuit->gates[i].id;
        }
    }
}

static void menu_list_connections(const Circuit *circuit, const int page_size)
{
    if (circuit == NULL) return;
    if (page_size <= 0) return;

    bool running = true;

    Pagination pagination;
    if (!pagination_create(&pagination, 0, page_size, circuit->connection_count)) return;

    while (running)
    {
        printf("Connection list: \n");
        printf("%-20s", "ID");
        printf("%-30s", "FROM");
        printf("%-30s", "TO");
        printf("TO INPUT\n");

        for (int i = pagination.start; i < pagination.end; i++)
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

        printf("________________________________________________________________________________________\n");
        printf("Page: %d/%d\n\n", pagination.page + 1, pagination.total_pages);
        if (pagination.page + 1 < pagination.total_pages) printf("[N] - Next\n");
        if (pagination.page > 0) printf("[P] - Previous\n");
        printf("[Q] - Back\n\n");

        char input;
        printf("> ");
        scanf(" %c", &input);

        switch (input)
        {
            case 'N':
            case 'n':
                pagination_next(&pagination);
                break;

            case 'P':
            case 'p':
                pagination_previous(&pagination);
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

#pragma endregion