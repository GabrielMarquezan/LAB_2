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

void insere_barra_zeros(char** matriz, int dimensoes[2])
{
    for(int i = 0; i < dimensoes[1]; i++)
    {
        matriz[i][dimensoes[0] + 1] = '\0';
    }
}

void preenche_matriz(char** matriz, int dimensoes[2])
{   
    int tamanho = ((dimensoes[0] * dimensoes[1])/2 + (dimensoes[0] * dimensoes[1]));
    char *guarda_string = malloc(tamanho * sizeof(char));
    int contador = 0;

    printf("Por favor, insira todos os caracteres de uma vez.\n");
    scanf("%s", &guarda_string);
    
    insere_barra_zeros(matriz, dimensoes);
    retira_espacos(guarda_string, tamanho);

    for(int i = 0; i < dimensoes[1]; i++)
    {
        for(int j = 0; j < dimensoes[0]; j++)
        {
            if(guarda_string[contador] != '\0')
            {
                matriz[i][j] = guarda_string[contador];
            }
            else break;

            contador++;
        }
    }
}

void retira_espacos(char guarda_string[], int tamanho)
{
    char aux[tamanho + 1];
    int contador = 0, step = 0;
    char fim = ' ';

    while(fim != '\0')
    {
        switch(step)
        {
            case 0:
                if(guarda_string[contador] == ' ') continue;

                aux[contador] = guarda_string[contador];
                fim = aux[contador];

                if(fim == '\0') 
                {
                    step = 1;
                    fim = ' ';
                    contador = 0;
                }

                break;
            
            case 1:
                guarda_string[contador] = aux[contador];
                break;
        }

        contador++;
    }
}

void imprime_matriz(char** matriz, int dimensoes[])
{
    for(int i = 0; i < dimensoes[1]; i++)
    {
        for(int j = 0; j < dimensoes[0]; j++)
        {
            printf("%c ", matriz[i][j]);
        }

        printf("\n");
    }
}
