#include <stdio.h>
#include "menu/connection_menu.h"
#include "utils/pagination.h"
#include "utils/string_utils.h"

void menu_list_connections(const Circuit *circuit, const int page_size)
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
            
            string_concat(from_gate_text, sizeof(from_gate_text), "(", gate_type_to_string(circuit->gates[connection->from_gate_id].type), ")");
            printf("%-7s%-23d", from_gate_text, connection->from_gate_id);

            string_concat(to_gate_text, sizeof(to_gate_text), "(", gate_type_to_string(circuit->gates[connection->to_gate_id].type), ")");
            printf("%-7s%-26d", to_gate_text, connection->to_gate_id);

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