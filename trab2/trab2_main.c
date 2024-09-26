#include <stdio.h>
#include <stdlib.h>
#include "trab2_func.h"

int main(void)
{
    //Structs essenciais
    Matriz matriz_caca_palavras = {NULL, -1, -1};
    Palavra palavra_buscada = {"mig", {-1, -1}, {-1, -1}};
    //Ponteiros
    Matriz *ponteiro_para_caca_palavras = &matriz_caca_palavras;
    Palavra *ponteiro_para_palavra_buscada = &palavra_buscada;


        le_dimensoes_matriz(ponteiro_para_caca_palavras);
        matriz_caca_palavras.matriz = aloca_matriz(matriz_caca_palavras.numero_de_linhas, matriz_caca_palavras.numero_de_colunas);
        inicializa_matriz(ponteiro_para_caca_palavras);
        preenche_matriz(ponteiro_para_caca_palavras);
        imprime_matriz(ponteiro_para_caca_palavras);
        busca_palavra(ponteiro_para_caca_palavras, ponteiro_para_palavra_buscada);


        printf("\n\nInício: %d, %d\n", palavra_buscada.inicio.y, palavra_buscada.inicio.x) ;
        printf("Fim: %d, %d\n\n", palavra_buscada.fim.y, palavra_buscada.fim.x);

        desaloca_matriz(ponteiro_para_caca_palavras);
}
