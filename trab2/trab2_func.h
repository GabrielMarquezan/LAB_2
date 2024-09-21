#ifndef TRAB2_FUNC_H
#define TRAB2_FUNC_H

void le_dimensoes_matriz(int dimensoes[]);
char** aloca_matriz(int dimensoes[2]);
void insere_barra_zeros(char** matriz, int dimensoes[2]);
void preenche_matriz(char** matriz, int dimensoes[2]);
void retira_espacos(char guarda_string[], int tamanho);
void imprime_matriz(char** matriz, int dimensoes[]);

#endif
