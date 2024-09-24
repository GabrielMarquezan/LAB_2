#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include "trab2_func.h"

//única função que altera as informações de "dimensoes_da_matriz"
void le_dimensoes_matriz(Dimensoes* dimensoes_da_matriz)
{
    printf("Qual será a largura do seu caça-palavras (colunas)?\n");
    scanf("%d", &dimensoes_da_matriz->colunas);

    printf("E a altura (linhas)?\n");
    scanf("%d", &dimensoes_da_matriz->linhas);
}

char** aloca_matriz(Dimensoes dimensoes_da_matriz)
{
    //Aloca as linhas da matriz dinamicamente e testa se houve êxito
    char** matriz = malloc(dimensoes_da_matriz.linhas * sizeof(char*));
    if(matriz == NULL)
    {
        printf("\n\nErro 1 na função 'aloca_matriz'\n\n");
        exit(1);
    }

    for(int i = 0; i < dimensoes_da_matriz.linhas; i++)
    {
        //Aloca as colunas da matriz dinamicamente e testa se houve êxito
        //OBS: (dimensoes_da_matriz.colunas + 1) serve para garantir o espaço do '\0' no fim da linha
        matriz[i] = malloc((dimensoes_da_matriz.colunas + 1) * sizeof(char));
        if(matriz[i] == NULL)
        {
            printf("\n\nErro 2 na função 'aloca_matriz'\n'i' referente ao erro: %d\n\n", i);
            exit(1);
        }
    }

    return matriz;
}

void inicializa_matriz(char** matriz, Dimensoes dimensoes_da_matriz)
{
    for(int i = 0; i < dimensoes_da_matriz.linhas; i++)
    {
        for(int j = 0; j < dimensoes_da_matriz.colunas; j++)
        {
            matriz[i][j] = ' ';
        }
    }
}

char* aloca_vetor_para_guardar_string(int tamanho_do_texto_para_matriz)
{
    //Aloca o vetor dinamicamente e testa se houve êxito
    char *texto_para_matriz = malloc(tamanho_do_texto_para_matriz * sizeof(char));
    if(texto_para_matriz == NULL)
    {
        printf("\n\nErro 1 na função 'aloca_vetor_para_guardar_string'\n\n");
        exit(1);
    }

    return texto_para_matriz;
}

void le_texto_para_matriz(char *texto_para_matriz, int tamanho_do_texto_para_matriz)
{
    printf("Por favor, insira todos os caracteres de uma vez.\n");
    //Esse getchar() captura o ENTER digitado por último para que o fgets() funcione corretamente
    getchar();
    fgets(texto_para_matriz, tamanho_do_texto_para_matriz, stdin);
}

void retira_espacos(char texto_para_matriz[], int tamanho_da_entrada)
{
    //Puxa todo o restante do texto para trás quando houver espaço
    for(int i = 0; i < tamanho_da_entrada; i++)
    {
        while(texto_para_matriz[i] == ' ' || texto_para_matriz[i] == '\n')
        {
            for(int j = i; j < tamanho_da_entrada - 1; j++) 
            {
                texto_para_matriz[j] = texto_para_matriz[j+1];
            }
        }
    }
}

void coloca_tudo_em_minusculo(char texto_para_matriz[], int tamanho_da_entrada)
{
    char aux = ' ';

    for(int i = 0; i < tamanho_da_entrada; i++)
    {
        aux = tolower(texto_para_matriz[i]);
        texto_para_matriz[i] = aux;
    }
}

void formatar_string_para_matriz(char texto_para_matriz[], int tamanho_da_entrada)
{
    retira_espacos(texto_para_matriz, tamanho_da_entrada);
    coloca_tudo_em_minusculo(texto_para_matriz, tamanho_da_entrada);
}

char* texto_pronto_para_matriz(Dimensoes dimensoes_da_matriz)
{
    /*tamanho_do_texto_para_matriz recebe um valor arbitrariamente maior que o alocado para garantir que 
    nada seja truncado pela existência de espaços na entrada do usuário*/
    int tamanho_do_texto_para_matriz = (dimensoes_da_matriz.linhas * dimensoes_da_matriz.colunas * 1.5);
    char* texto_para_matriz = aloca_vetor_para_guardar_string(tamanho_do_texto_para_matriz);

    le_texto_para_matriz(texto_para_matriz,tamanho_do_texto_para_matriz);
    formatar_string_para_matriz(texto_para_matriz, tamanho_do_texto_para_matriz);

    return texto_para_matriz;
}

void insere_barra_zeros(char** matriz, Dimensoes dimensoes_da_matriz)
{
    //Garante que haverá '\0' no fim das linhas
    for(int i = 0; i < dimensoes_da_matriz.linhas; i++) matriz[i][dimensoes_da_matriz.colunas] = '\0';
}

void preenche_matriz(char** matriz, Dimensoes dimensoes_da_matriz)
{   
    char* texto_para_matriz = texto_pronto_para_matriz(dimensoes_da_matriz);
    int contador = 0;

    //Preenche a matriz com a entrada de dados devidamente tratada
    for(int i = 0; i < dimensoes_da_matriz.linhas; i++)
    {
        for(int j = 0; j < dimensoes_da_matriz.colunas; j++)
        {
            if(texto_para_matriz[contador] == '\0') break;
            
            matriz[i][j] = texto_para_matriz[contador];
            contador++;
        }

        if(texto_para_matriz[contador] == '\0') break;
    }

    insere_barra_zeros(matriz, dimensoes_da_matriz);
}

void imprime_matriz(char** matriz, Dimensoes dimensoes_da_matriz)
{
    printf("\n   ");

    //Imprime o índice das colunas
    for(int i = 0; i < dimensoes_da_matriz.colunas; i++)
    {
        if(i < 9) 
        {
            printf("| %d ", i + 1);
        }
        else printf("| %d", i + 1);
    }

    printf("|\n");

    for(int i = 0; i < dimensoes_da_matriz.linhas; i++)
    {
        //Divide as linhas
        for(int i = 0; i < 4 * dimensoes_da_matriz.colunas + 4; i++) printf("-");
        
        //Imprime o índice das linhas
        printf("\n %d ", i + 1);

        //Imprime o conteúdo da matriz
        for(int j = 0; j < dimensoes_da_matriz.colunas; j++)
        {
            if(matriz[i][j] >= 97 || matriz[i][j] <= 122) printf("| %c ", matriz[i][j]);
        }

        printf("|\n");
    }

    printf("\n");
}

void desaloca_matriz(char** matriz, Dimensoes dimensoes_da_matriz)
{
    for(int i = 0; i < dimensoes_da_matriz.linhas; i++) free(matriz[i]);
    free(matriz);
}
