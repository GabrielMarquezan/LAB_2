#include "trab2_func.h"

//única função que altera as informações de "dimensoes_da_matriz"
void le_dimensoes_matriz(Matriz* matriz)
{
    printf("Qual será a largura do seu caça-palavras (colunas)?\n");
    scanf("%d", &matriz->numero_de_colunas);

    printf("E a altura (linhas)?\n");
    scanf("%d", &matriz->numero_de_linhas);
}

char** aloca_matriz(int linhas, int colunas)
{
    //Aloca as linhas da matriz dinamicamente e testa se houve êxito
    char** matriz = malloc(linhas * sizeof(char*));
    if(matriz == NULL)
    {
        printf("\n\nErro 1 na função 'aloca_matriz'\n\n");
        exit(1);
    }

    for(int i = 0; i < linhas; i++)
    {
        //Aloca as colunas da matriz dinamicamente e testa se houve êxito
        //OBS: (colunas + 1) serve para garantir o espaço do '\0' no fim da linha
        matriz[i] = malloc((colunas + 1) * sizeof(char));
        if(matriz[i] == NULL)
        {
            printf("\n\nErro 2 na função 'aloca_matriz'\n'i' referente ao erro: %d\n\n", i);
            exit(1);
        }
    }

    return matriz;
}

void inicializa_matriz(Matriz* matriz)
{
    for(int i = 0; i < matriz->numero_de_linhas; i++)
    {
        for(int j = 0; j < matriz->numero_de_colunas; j++) matriz->matriz[i][j] = ' ';
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

void le_texto_para_matriz(char texto_para_matriz[], int tamanho_do_texto_para_matriz)
{
    printf("Por favor, insira todos os caracteres de uma vez.\n");
    //Esse getchar() captura o ENTER digitado por último para que o fgets() funcione corretamente
    getchar();
    fgets(texto_para_matriz, tamanho_do_texto_para_matriz, stdin);
}

void retira_espacos(char texto_para_matriz[], int tamanho_do_texto_para_matriz)
{
    //Puxa todo o restante do texto para trás quando houver espaço
    for(int i = 0; i < tamanho_do_texto_para_matriz; i++)
    {
        while(texto_para_matriz[i] == ' ' || texto_para_matriz[i] == '\n')
        {
            for(int j = i; j < tamanho_do_texto_para_matriz - 1; j++) texto_para_matriz[j] = texto_para_matriz[j+1];
        }
    }
}

void coloca_tudo_em_minusculo(char texto_para_matriz[], int tamanho_do_texto_para_matriz)
{
    char aux = ' ';

    for(int i = 0; i < tamanho_do_texto_para_matriz; i++)
    {
        aux = tolower(texto_para_matriz[i]);
        texto_para_matriz[i] = aux;
    }
}

void formatar_string_para_matriz(char texto_para_matriz[], int tamanho_do_texto_para_matriz)
{
    retira_espacos(texto_para_matriz, tamanho_do_texto_para_matriz);
    coloca_tudo_em_minusculo(texto_para_matriz, tamanho_do_texto_para_matriz);
}

char* texto_pronto_para_matriz(int linhas, int colunas)
{
    /*tamanho_do_texto_para_matriz recebe um valor arbitrariamente maior que o alocado para garantir que 
    nada seja truncado pela existência de espaços na entrada do usuário*/
    int tamanho_do_texto_para_matriz = (linhas * colunas * 1.5);
    char* texto_para_matriz = aloca_vetor_para_guardar_string(tamanho_do_texto_para_matriz);

    le_texto_para_matriz(texto_para_matriz,tamanho_do_texto_para_matriz);
    formatar_string_para_matriz(texto_para_matriz, tamanho_do_texto_para_matriz);

    return texto_para_matriz;
}

void insere_barra_zeros(Matriz* matriz)
{
    //Garante que haverá '\0' no fim das linhas
    for(int i = 0; i < matriz->numero_de_linhas; i++) matriz->matriz[i][matriz->numero_de_colunas] = '\0';
}

void preenche_matriz(Matriz* matriz)
{   
    char* texto_para_matriz = texto_pronto_para_matriz(matriz->numero_de_linhas, matriz->numero_de_colunas);
    int contador = 0;

    //Preenche a matriz com a entrada de dados devidamente tratada
    for(int i = 0; i < matriz->numero_de_linhas; i++)
    {
        for(int j = 0; j < matriz->numero_de_colunas; j++)
        {
            if(texto_para_matriz[contador] == '\0') break;
            
            matriz->matriz[i][j] = texto_para_matriz[contador];
            contador++;
        }

        if(texto_para_matriz[contador] == '\0') break;
    }

    insere_barra_zeros(matriz);
}

void imprime_matriz(Matriz* matriz)
{
    printf("\n   ");

    //Imprime o índice das colunas
    for(int i = 0; i < matriz->numero_de_colunas; i++)
    {
        if(i < 9) 
        {
            printf("| %d ", i + 1);
        }
        else printf("| %d", i + 1);
    }

    printf("|\n");

    for(int i = 0; i < matriz->numero_de_linhas; i++)
    {
        //Divide as linhas
        for(int i = 0; i < 4 * matriz->numero_de_colunas + 4; i++) printf("-");
        
        //Imprime o índice das linhas
        printf("\n %d ", i + 1);

        //Imprime o conteúdo da matriz
        for(int j = 0; j < matriz->numero_de_colunas; j++)
        {
            if(matriz->matriz[i][j] >= 97 || matriz->matriz[i][j] <= 122) printf("| %c ", matriz->matriz[i][j]);
        }

        printf("|\n");
    }

    printf("\n");
}

void desaloca_matriz(Matriz* matriz)
{
    for(int i = 0; i < matriz->numero_de_linhas; i++) free(matriz->matriz[i]);
    free(matriz->matriz);
}

int seleciona_sentido_da_busca(void)
{
    int opcao_de_busca = -1;

    do
    {
        printf("Em que sentido você deseja realizar a busca?\n");
        printf("1 - Horizontal direta\n");
        printf("2 - Horizontal inversa\n");
        printf("3 - Vertical direta\n");
        printf("4 - Vertical inversa\n");
        printf("5 - Diagonal direta\n");
        printf("6 - Diagonal inversa\n");
        printf("Insira o número de sua opção: ");
        scanf("%d", &opcao_de_busca);
    }
    while(opcao_de_busca < 1 || opcao_de_busca > 6);

    return opcao_de_busca;
}

void inverte_string(char string[], int tamanho)
{
    char auxiliar = ' ';
    int indice_inverso = tamanho;

    for(int i = 0; i < tamanho / 2; i++)
    {
        auxiliar = string[i];
        string[i] = string[indice_inverso - 1];
        string[indice_inverso - 1] = auxiliar;
        indice_inverso--;
    }
}

void calcula_fim_da_palavra(Palavra* palavra_buscada, int tipo_de_busca)
{
    switch(tipo_de_busca)
    {
        case 1:
            palavra_buscada->fim.x = palavra_buscada->inicio.x + strlen(palavra_buscada->palavra) - 1;
            palavra_buscada->fim.y = palavra_buscada->inicio.y;
            break;
        case 2:
            palavra_buscada->fim.x = palavra_buscada->inicio.x - strlen(palavra_buscada->palavra) + 1;
            palavra_buscada->fim.y = palavra_buscada->inicio.y;
            break;
    }
}

void atualiza_posicao_da_palavra(Matriz* matriz, char* endereco_base, Palavra* palavra_buscada, int tipo_de_busca)
{
    for(int i = 0; i < matriz->numero_de_linhas; i++)
    {
        for(int j = 0; j < matriz->numero_de_colunas; j++)
        {
            if(endereco_base == &matriz->matriz[i][j])
            {
                palavra_buscada->inicio.x = j + 1;
                palavra_buscada->inicio.y = i + 1;
                calcula_fim_da_palavra(palavra_buscada, tipo_de_busca);
            }
        }
    }
}

char* busca_palavra_horizontal_direta(Matriz* matriz, Palavra* palavra_buscada)
{
    char* primeiro_endereco_palavra = NULL;

    for(int i = 0; i < matriz->numero_de_linhas; i++)
    {
        primeiro_endereco_palavra = strstr(matriz->matriz[i], palavra_buscada->palavra);
        if(primeiro_endereco_palavra != NULL) return primeiro_endereco_palavra;
    }

    return primeiro_endereco_palavra;
}

char* busca_palavra_horizontal_inversa(Matriz* matriz, Palavra* palavra_buscada)
{
    char* primeiro_endereco_palavra = NULL;

    //Inverte a palavra buscada 
    inverte_string(palavra_buscada->palavra, strlen(palavra_buscada->palavra));

    for(int i = 0; i < matriz->numero_de_linhas; i++)
    {
        primeiro_endereco_palavra = strstr(matriz->matriz[i], palavra_buscada->palavra);
        if(primeiro_endereco_palavra != NULL) return primeiro_endereco_palavra;
    }

    return primeiro_endereco_palavra;
}

void busca_palavra(Matriz* matriz, Palavra* palavra_buscada)
{
    int opcao_de_busca = seleciona_sentido_da_busca();
    char* primeiro_endereco_palavra = NULL;

    switch(opcao_de_busca)
    {
        case 1:
            primeiro_endereco_palavra = busca_palavra_horizontal_direta(matriz, palavra_buscada);
            break;
        case 2:
            primeiro_endereco_palavra = busca_palavra_horizontal_inversa(matriz, palavra_buscada);
            break;
    }

    if(primeiro_endereco_palavra != NULL) 
    {
        atualiza_posicao_da_palavra(matriz, primeiro_endereco_palavra, palavra_buscada, opcao_de_busca);
    }
}
