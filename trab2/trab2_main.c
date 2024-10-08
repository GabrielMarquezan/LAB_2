#include <stdio.h>
#include <stdlib.h>
#include "trab2_func.h"

int main(void)
{
    //Structs essenciais
    Matriz matriz_caca_palavras = {NULL, NULL, -1, -1};
    Coordenadas posicoes_palavra_buscada = {{-1, -1}, {-1, -1}};
    //Ponteiros
    Matriz *ponteiro_para_caca_palavras = &matriz_caca_palavras;
    Coordenadas *ponteiro_para_posicoes_palavra_buscada = &posicoes_palavra_buscada;
    //Resto
    int tamanho_palavra_buscada = 0;

    deixa_matriz_pronta(ponteiro_para_caca_palavras);

    if(matriz_caca_palavras.numero_de_colunas > matriz_caca_palavras.numero_de_linhas)
    {
        tamanho_palavra_buscada = matriz_caca_palavras.numero_de_colunas + 1;
    }
    else tamanho_palavra_buscada = matriz_caca_palavras.numero_de_linhas + 1;

    char palavra_buscada[tamanho_palavra_buscada];

    while(true)
    {
        imprime_matriz(matriz_caca_palavras.matriz, matriz_caca_palavras.numero_de_linhas, matriz_caca_palavras.numero_de_colunas);
        inicializa_vetor_de_char(palavra_buscada, tamanho_palavra_buscada);
        le_palavra_buscada(palavra_buscada, matriz_caca_palavras);
        busca_palavra(ponteiro_para_caca_palavras, ponteiro_para_posicoes_palavra_buscada, palavra_buscada);
        imprime_posicoes_palavra(posicoes_palavra_buscada);

        if(!deseja_continuar_jogando()) break;
    }

    printf("\n\nFIM DE JOGO\n\n");

    desaloca_matriz_e_transposta(ponteiro_para_caca_palavras);
}
