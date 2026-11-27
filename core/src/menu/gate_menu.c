#include <stdio.h>
#include "menu/gate_menu.h"
#include "console/input.h"
#include "gate.h"
#include "utils/pagination.h"

void menu_add_gate(Circuit *circuit)
{
    if (circuit == NULL) return;

    printf("\n=== Choice a gate type ===\n");
    for (int i = 0; i < GATE_TYPE_COUNT; i++)
        printf("%d. %s\n", i + 1, gate_type_to_string((GateType)i));

    printf("> ");

    int input;
    if (!input_read_int_range(&input, 1, GATE_TYPE_COUNT, RANGE_LEFT_CLOSED))
    {
        printf("Invalid option\n");
        return;
    }

    GateType type = (GateType)(input - 1);

    int gate_id = circuit_add_gate(circuit, type);

    if (gate_id == -1)
    {
        printf("Failed to add Gate\n");
        return;
    }

    printf("Gate created. ID: %d\n", gate_id);
}

void menu_connect_gate(Circuit *circuit)
{
    printf("Select from gate: ");
    int from_gate_id = menu_select_gate(circuit, 15);
    if (from_gate_id == -1) return;

    printf("Select to gate: ");
    int to_gate_id = menu_select_gate(circuit, 15);
    if (to_gate_id == -1) return;

    for (int i = 0; i < INPUT_COUNT; i++)
        printf("%d. %s\n", i + 1, gate_input_to_string((GateInput)i));

    printf("Select input: ");

    int input;
    scanf("%d", &input);

    if (input < 1 || input > INPUT_COUNT)
    {
        printf("Invalid option\n");
        return;
    }

    GateInput gate_input = (GateInput)(input - 1);

    int connection = circuit_connect_gate(circuit, from_gate_id, to_gate_id, gate_input);

    printf("Connection created: %d", connection);
}

void menu_delete_gate(Circuit *circuit)
{
    printf("Select gate to delete: ");
    int delete_gate_id = menu_select_gate(circuit, 15);
    if (delete_gate_id == -1) return;

    if (!circuit_remove_gate(circuit, delete_gate_id))
    {
        printf("Cannot delete the gate");
        return;
    }
}

void menu_set_source_gate_output(Circuit *circuit)
{
    printf("Select gate to set output: ");
    int source_gate_id = menu_select_source_gate(circuit, 15);
    if (source_gate_id == -1) return;

    Gate *source_gate = circuit_get_gate_by_id(circuit, source_gate_id);
    
    if (source_gate == NULL) return;

    printf("Set the output value: ");
    int value;
    scanf("%d", &value);

    if (value < 0 || value > 1) return;

    if (!gate_set_switch_state(source_gate, (bool)value))
    {
        printf("Cannot set the gate output");
        return;
    }
}

void menu_list_gates(const Circuit *circuit, const int page_size)
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
        printf("%-15s", "INPUT B");
        printf("OUTPUT\n");

        for (int i = pagination.start; i < pagination.end; i++)
        {
            printf("%-20d", circuit->gates[i].id);
            printf("%-17s", gate_type_to_string(circuit->gates[i].type));
            printf("%-15d", circuit->gates[i].inputs[INPUT_A]);

            // Если тип гейта NOT то в колонке INPUT B ставим "-", если нет показываем значение инпута
            if (circuit->gates[i].type == GATE_NOT)
                printf("%-15s", "-");
            else
                printf("%-15d", circuit->gates[i].inputs[INPUT_B]);

            printf("%d\n", circuit->gates[i].output);
        }

        printf("_________________________________________________________________________\n");
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

int menu_select_gate(const Circuit *circuit, const int page_size)
{
    if (circuit == NULL) return -1;
    if (page_size <= 0) return -1;

    Pagination pagination;
    if (!pagination_create(&pagination, 0, page_size, circuit->gate_count)) return -1;

    while (true)
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
            printf("%-15d", circuit->gates[i].inputs[INPUT_A]);

            // Если тип гейта NOT то в колонке INPUT B ставим "-", если нет показываем значение инпута
            if (circuit->gates[i].type == GATE_NOT)
                printf("%s\n", "-");
            else
                printf("%d\n", circuit->gates[i].inputs[INPUT_B]);
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

int menu_select_source_gate(const Circuit *circuit, const int page_size)
{
    if (circuit == NULL) return -1;
    if (page_size <= 0) return -1;

    Pagination pagination;
    if (!pagination_create(&pagination, 0, page_size, circuit->gate_count)) return -1;

    while (true)
    {
        printf("\nGate list: \n");
        printf("%-20s", "ID");
        printf("%-15s", "NAME");
        printf("OUTPUT\n");

        for (int i = pagination.start; i < pagination.end; i++)
        {
            if (gate_is_source(circuit->gates[i].type))
            {
                printf("%-20d", circuit->gates[i].id);
                printf("%-17s", gate_type_to_string(circuit->gates[i].type));
                printf("%d\n", circuit->gates[i].output);
            }  
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
                if (circuit->gates[i].id == id && gate_is_source(circuit->gates[i].type)) return circuit->gates[i].id;
        }
    }
}