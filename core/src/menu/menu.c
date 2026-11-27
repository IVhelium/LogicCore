#include "menu/menu.h"
#include "console/input.h"
#include "menu/gate_menu.h"
#include <stdio.h>


// Circuit
static void menu_create_circuit(void);
static void menu_circuit(Circuit *circuit);

void menu_init(void) {
  bool running = true;

  while (running) {
    int input;

    printf("\n1. Create Circuit\n");
    printf("2. Open circuit\n");
    printf("3. Exit\n");

    printf("> ");
    // scanf("%d", &input);
    if (!input_read_int(&input))
      return;

    switch (input) {
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

static void menu_create_circuit(void) {
  // Ввод имени и инициализация схемы
  char name[MAX_NAME_LENGTH];

  printf("Insert name of the circuit: ");
  if (!input_read_string(name, sizeof(name)))
    return;

  Circuit circuit;

  circuit_init(&circuit, name);
  menu_circuit(&circuit);
}

static void menu_circuit(Circuit *circuit) {
  if (circuit == NULL)
    return;

  bool running = true;

  while (running) {
    int input;

    printf("\n=== Circuit: %s ===\n", circuit->name);

    printf("1. Add Gate\n");
    printf("2. Connect Gates\n");
    printf("3. Delete Gate\n");
    printf("4. Set Source Gate Output\n");
    printf("5. Circuit Run\n");
    printf("6. Exit\n");

    printf("> ");
    if (!input_read_int(&input))
      return;
    // scanf("%d", &input);

    switch (input) {
    case 1:
      menu_add_gate(circuit);
      break;

    case 2:
      menu_connect_gate(circuit);
      break;

    case 3:
      menu_delete_gate(circuit);
      break;

    case 4:
      menu_set_source_gate_output(circuit);
      break;

    case 5:
      circuit_simulate(circuit);
      menu_list_gates(circuit, 15);
      break;

    case 6:
      running = false;
      break;

    default:
      printf("Invalid option\n");
      break;
    }
  }
}