#include <stdio.h>
#include "menu.h"

static void menu_create_circuit(void);
static void menu_circuit(Circuit *circuit);


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

        /*
            Создать вентиль,
            Соединить конкретные вентили,
            Запустить схему,
            Удалить вентиль
        */
        printf("\n=== Circuit: %s ===\n", circuit->name);

        printf("1. Create Gate\n");
        printf("2. Connect Gates\n");
        printf("3. Delete Gate\n");
        printf("4. Circuit Run\n");
        printf("5. Exit\n");

        printf("> ");
        scanf("%d", &choice);

        switch (choice)
        {
            case 5:
                running = false;
                break;
        }
    }
}

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