#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "trab2_func.h"

int main(void)
{
    int dimensoes[2] = {0, 0};
    char** matriz;

    while(true)
    {
        le_dimensoes_matriz(dimensoes);
        matriz = aloca_matriz(dimensoes);
        preenche_matriz(matriz, dimensoes);
    }
}
