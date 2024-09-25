#include <stdio.h>
#include <stdlib.h>
#include "trab2_func.h"

int main(void)
{
    Dimensoes dimensoes_da_matriz = {0, 0};
    Dimensoes* ponteiro_para_dimensoes_da_matriz = &dimensoes_da_matriz;
    char** matriz = NULL;
    int posicao_palavra[2] = {-1, -1};
    char buscada[] = "mig";

        le_dimensoes_matriz(ponteiro_para_dimensoes_da_matriz);
        matriz = aloca_matriz(dimensoes_da_matriz);
        inicializa_matriz(matriz, dimensoes_da_matriz);
        preenche_matriz(matriz, dimensoes_da_matriz);
        imprime_matriz(matriz, dimensoes_da_matriz);
        busca_palavra(matriz, dimensoes_da_matriz, posicao_palavra, buscada);

        if(posicao_palavra[0] >= 0 && posicao_palavra[1] >= 0) 
        {
            printf("\n\n%d, %d\n\n", posicao_palavra[0] + 1, posicao_palavra[1] + 1);
        }

        desaloca_matriz(matriz, dimensoes_da_matriz);
}
