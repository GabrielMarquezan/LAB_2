#include <stdio.h>
#include <stdlib.h>
#include "trab2_func.h"

int main(void)
{
    Dimensoes dimensoes_da_matriz = {0, 0};
    Dimensoes* ponteiro_para_dimensoes_da_matriz = &dimensoes_da_matriz;
    char** matriz = NULL;

        le_dimensoes_matriz(ponteiro_para_dimensoes_da_matriz);
        matriz = aloca_matriz(dimensoes_da_matriz);
        preenche_matriz(matriz, dimensoes_da_matriz);
        imprime_matriz(matriz, dimensoes_da_matriz);
    
}