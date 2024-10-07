#ifndef TRAB2_FUNC_H
#define TRAB2_FUNC_H

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

typedef struct
{
    char** matriz;
    char** transposta;
    int numero_de_linhas;
    int numero_de_colunas;
} Matriz;

typedef struct
{
    int x;
    int y;
} Ponto;

typedef struct
{
    Ponto inicio;
    Ponto fim;
} Coordenadas;

void le_dimensoes_matriz(Matriz* matriz);

char** aloca_matriz(int linhas, int colunas);
//Aloca um vetor de ponteiros dinamicamente de acordo com as dimensões informadas pelo usuário

void inicializa_matriz(Matriz* matriz);
//Preenche a matriz com espaços para garantir que não haja lixo

void le_texto_para_matriz(char texto_para_matriz[], int tamanho_do_texto_para_matriz);

void retira_espacos(char texto_para_matriz[], int tamanho_do_texto_para_matriz);
//Puxa o texto para trás até que qualquer espaço ou '\n' suma

void coloca_tudo_em_minusculo(char texto_para_matriz[], int tamanho_do_texto_para_matriz);

void formatar_string_para_matriz(char texto_para_matriz[], int tamanho_do_texto_para_matriz);
//Chama 'coloca_tudo_em_minusculo' e 'insere_barra_zeros'

void texto_pronto_para_matriz(char texto_para_matriz[], int tamanho_do_texto_para_matriz);
//Retorna a string tratada e pronta para o uso na matriz

void insere_barra_zeros(Matriz* matriz);
//Insere '\0' no fim da linha da matriz

void preenche_matriz(Matriz* matriz);
//Preenche com o texto informado pelo usuário

void imprime_matriz(char** matriz, int linhas, int colunas);

void desaloca_matriz_e_transposta(Matriz* matriz);

void le_palavra_buscada(char palavra_buscada[], Matriz matriz);

int seleciona_sentido_da_busca(void);

void inverte_string(char string[], int tamanho);

void calcula_fim_da_palavra(Coordenadas* posicoes, char palavra_buscada[], int tipo_de_busca);
//Calcula a posição do útlimo caracter da palavra de acordo com o seu tamanho e o tipo de busca feito

void atualiza_posicao_da_palavra(Matriz* matriz, char* endereco_base, Coordenadas* posicoes, char palavra_buscada[], int tipo_de_busca);
//Altera pontos de inicio e fim da estrutura "posicoes_palavra_buscada"

void transpoe_matriz(Matriz* matriz);
//Transformação necessária para facilitar pesquisa na vertical

void busca_diagonal_principal(Matriz* matriz, Coordenadas* posicoes, char palavra_buscada[], bool inversa);
void busca_diagonal_secundaria(Matriz* matriz, Coordenadas* posicoes, char palavra_buscada[], bool inversa);
//Funções de busca diagonal são necessárias devido à natureza da busca (não há transformação da matriz que possibilite uma busca igual às demais)
//Essas funções alteram diretamente a posição da palavra buscada

void busca_palavra(Matriz* matriz, Coordenadas* posicoes, char palavra_buscada[]);
//Agrupa todos os tipos de busca

#endif
