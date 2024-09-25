#ifndef TRAB2_FUNC_H
#define TRAB2_FUNC_H

typedef struct
{
    int linhas;
    int colunas;
} Dimensoes;

void le_dimensoes_matriz(Dimensoes* dimensoes_da_matriz);

char** aloca_matriz(Dimensoes dimensoes_da_matriz);
//Aloca um vetor de ponteiros dinamicamente de acordo com as dimensões informadas pelo usuário

void inicializa_matriz(char** matriz, Dimensoes dimensoes_da_matriz);
//Preenche a matriz com espaços para garantir que não haja lixo

char* aloca_vetor_para_guardar_string(int tamanho_do_texto_para_matriz);

void le_texto_para_matriz(char *texto_para_matriz, int tamanho_do_texto_para_matriz);

void retira_espacos(char texto_para_matriz[], int tamanho_da_entrada);
//Puxa o texto para trás até que qualquer espaço ou '\n' suma

void coloca_tudo_em_minusculo(char texto_para_matriz[], int tamanho_da_entrada);

void formatar_string_para_matriz(char texto_para_matriz[], int tamanho_da_entrada);
//Chama 'coloca_tudo_em_minusculo' e 'insere_barra_zeros'

char* texto_pronto_para_matriz(Dimensoes dimensoes_da_matriz);
//Retorna a string tratada e pronta para o uso na matriz

void insere_barra_zeros(char** matriz, Dimensoes dimensoes_da_matriz);
//Insere '\0' no fim da linha da matriz

void preenche_matriz(char** matriz, Dimensoes dimensoes_da_matriz);
//Preenche com o texto informado pelo usuário

void imprime_matriz(char** matriz, Dimensoes dimensoes_da_matriz);

void desaloca_matriz(char** matriz, Dimensoes dimensoes_da_matriz);

int seleciona_sentido_da_busca(void);

void inverte_string(char string[], int tamanho_da_string);

void atualiza_posicao_da_palavra(char** matriz, char* endereco_base, int posicoes[2], Dimensoes dimensoes_da_matriz);

char* busca_palavra_horizontal_direta(char** matriz, Dimensoes dimensoes_da_matriz, char palavra_buscada[]);

void busca_palavra_horizontal(char** matriz, Dimensoes dimensoes_da_matriz, int posicoes[], char palavra_buscada[]);

void busca_palavra(char** matriz, Dimensoes dimensoes_da_matriz, int posicoes[], char palavra_buscada[]);

#endif
