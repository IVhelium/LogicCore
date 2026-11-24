#pragma once

#include "circuit.h"

void menu_add_gate(Circuit *circuit);
void menu_connect_gate(Circuit *circuit);
void menu_delete_gate(Circuit *circuit);
void menu_set_source_gate_output(Circuit *circuit);
void menu_list_gates(const Circuit *circuit, const int page_size);
int menu_select_gate(const Circuit *circuit, const int page_size);
int menu_select_source_gate(const Circuit *circuit, const int page_size);