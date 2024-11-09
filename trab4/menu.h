#ifndef MENU_H
#define MENU_H

#include "mesas.h"

void imprime_menu();
int processa_escolha(Mesa*** mesas, Pilha_de_Pratos** pilha, Fila_de_Espera** fila, int* linhas, int* colunas, bool* restaurante_aberto);

#endif
