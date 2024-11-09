#ifndef MESAS_H
#define MESAS_H

#define MAX_LUGARES_POR_MESA 4

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct mesa {
    int id;
    bool ocupada;
    int lugares_ocupados;
    Prato* pratos_utilizados[MAX_LUGARES_POR_MESA];
    int comanda;
} Mesa;

typedef struct fila_de_espera
{
    int posicao;
    int tamanho_do_grupo;
    struct fila_de_espera* proximo_grupo;
} Fila_de_Espera;

typedef struct prato
{
    int id;
} Prato;

typedef struct pilha_de_pratos
{
    Prato* prato;
    struct pilha_de_pratos* proximo_prato;
} Pilha_de_Pratos;

Mesa** aloca_matriz_de_mesas(int n_linhas, int n_colunas);
void desaloca_matriz_de_mesas(Mesa** matriz, int n_linhas);
Pilha_de_Pratos* cria_pilha_vazia();
void inicializa_pilha_de_pratos(Pilha_de_Pratos** pilha, int numero_de_pratos);
void desaloca_pilha_de_pratos(Pilha_de_Pratos** pilha);
void empilha_prato(Pilha_de_Pratos** pilha, Prato* prato);
Prato* desempilha_prato(Pilha_de_Pratos** pilha);
void inicializa_mesas(Mesa** mesas, Pilha_de_Pratos** pilha, int n_linhas, int n_colunas);
Fila_de_Espera* cria_fila_de_espera();
void desaloca_fila_de_espera(Fila_de_Espera** fila);
void adiciona_grupo_na_fila(Fila_de_Espera** fila);
int remove_grupo_da_fila(Fila_de_Espera** fila);
void inicializar_restaurante(Mesa*** mesas, Pilha_de_Pratos** pilha, bool* restaurante_abertos);
Mesa* busca_mesa(Mesa** mesas, int linhas, int colunas, int id_mesa);
void arruma_mesa(Mesa* mesa, Pilha_de_Pratos** pilha);
void libera_mesa(Fila_de_Espera** fila, Pilha_de_Pratos** pilha, Mesa** mesas, int linhas, int colunas, int id_mesa);
void ocupa_mesa(Fila_de_Espera** fila, Mesa** mesas, Pilha_de_Pratos** pilha, int id_mesa, int linhas, int colunas);
void imprime_pilha_de_pratos(Pilha_de_Pratos* pilha);
void imprime_fila_de_espera(Fila_de_Espera* fila);
void imprime_ocupacao_das_mesas(Mesa** mesas, int linhas, int colunas);

#endif
