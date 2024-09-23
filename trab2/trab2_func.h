#ifndef TRAB2_FUNC_H
#define TRAB2_FUNC_H

typedef struct
{
    int linhas;
    int colunas;
} Dimensoes;

void le_dimensoes_matriz(Dimensoes* dimensoes_da_matriz);
char** aloca_matriz(Dimensoes dimensoes_da_matriz);
void insere_barra_zeros(char** matriz, Dimensoes dimensoes_da_matriz);
void retira_espacos(char texto_para_matriz[], int tamanho_da_entrada);
void coloca_tudo_em_minusculo(char texto_para_matriz[], int tamanho_da_entrada);
void formatar_string_para_matriz(char texto_para_matriz[], int tamanho_da_entrada);
void preenche_matriz(char** matriz, Dimensoes dimensoes_da_matriz);
void imprime_matriz(char** matriz, Dimensoes dimensoes_da_matriz);

#endif
