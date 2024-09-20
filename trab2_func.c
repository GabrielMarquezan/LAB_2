#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include "trab2_func.h"

void le_dimensoes_matriz(int dimensoes[2])
{
    printf("Qual será a largura do seu caça-palavras (colunas)?\n");
    scanf("%d", &dimensoes[0]);

    printf("E a altura (linhas)?\n");
    scanf("%d", &dimensoes[1]);
}

char** aloca_matriz(int dimensoes[2])
{
    char** matriz = malloc(dimensoes[1] * sizeof(char*));

    for(int i = 0; i < dimensoes[1]; i++)
    {
        matriz[i] = malloc((dimensoes[0] + 1) * sizeof(char));
    }

    return matriz;
}

void preenche_matriz(char** matriz, int dimensoes[2])
{   
    char guarda_string[dimensoes[0] * dimensoes[1] + 1];
    int contador = 0;

    printf("Por favor, insira todos os caracteres de uma vez.\n");
    gets(guarda_string);

    for(int i = 0; i < dimensoes[1]; i++)
    {
        for(int j = 0; j < dimensoes[0]; j++)
        {
            matriz[i][j] = guarda_string[contador];

            contador++;
        }
    }
}

void retira_espacos(char guarda_string[], int tamanho)
{
    char aux[tamanho + 1];
    int contador = 0;
    char fim = ' ';

    while(fim != '\0')
    {
        switch()
        {
            case 0:
                if(guarda_string[contador] == ' ') continue;

                aux[contador] = guarda_string[contador];
                fim = aux[contador];
                break;
        
        }
    }
}
