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
    char** matriz = (char**) malloc(linhas * sizeof(char*));
    if(matriz == NULL)
    {
        printf("\n\nErro 1 na função 'aloca_matriz'\n\n");
        exit(1);
    }

    for(int i = 0; i < linhas; i++)
    {
        //Aloca as colunas da matriz dinamicamente e testa se houve êxito
        //OBS: (colunas + 1) serve para garantir o espaço do '\0' no fim da linha
        matriz[i] = (char*) malloc((colunas + 1) * sizeof(char));
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

void texto_pronto_para_matriz(char texto_para_matriz[], int tamanho_do_texto_para_matriz)
{
    le_texto_para_matriz(texto_para_matriz,tamanho_do_texto_para_matriz);
    formatar_string_para_matriz(texto_para_matriz, tamanho_do_texto_para_matriz);
    texto_para_matriz[tamanho_do_texto_para_matriz - 1] = '\0';
}

void insere_barra_zeros(Matriz* matriz)
{
    //Garante que haverá '\0' no fim das linhas
    for(int i = 0; i < matriz->numero_de_linhas; i++) matriz->matriz[i][matriz->numero_de_colunas] = '\0';
}

void preenche_matriz(Matriz* matriz)
{   
    /*texto para matriz tem um tamanho arbitrariamente maior que o alocado para garantir que 
    nada seja truncado pela existência de espaços na entrada do usuário*/
    int tamanho_do_texto_para_matriz = matriz->numero_de_linhas * matriz->numero_de_colunas * 1.5;
    char texto_para_matriz[tamanho_do_texto_para_matriz];

    texto_pronto_para_matriz(texto_para_matriz, tamanho_do_texto_para_matriz);
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

void imprime_matriz(char** matriz, int linhas, int colunas)
{
    printf("\n    ");

    //Imprime o índice das colunas
    for(int i = 0; i < colunas; i++)
    {
        if(i < 9) 
        {
            printf("| 0%d ", i + 1);
        }
        else printf("| %d ", i + 1);
    }

    printf("|\n");

    for(int i = 0; i < linhas; i++)
    {
        //Divide as linhas
        for(int i = 0; i < 5 * colunas + 5; i++) printf("-");
        
        //Imprime o índice das linhas
        if(i < 9)
        {
           printf("\n 0%d ", i + 1); 
        } 
        else printf("\n %d ", i + 1);

        //Imprime o conteúdo da matriz
        for(int j = 0; j < colunas; j++)
        {
            if(matriz[i][j] >= 97 || matriz[i][j] <= 122) printf("|  %c ", matriz[i][j]);
        }

        printf("|\n");
    }

    printf("\n");
}

void desaloca_matriz_e_transposta(Matriz* matriz)
{
    for(int i = 0; i < matriz->numero_de_linhas; i++) free(matriz->matriz[i]);
    free(matriz->matriz);

    for(int i = 0; i < matriz->numero_de_colunas; i++) free(matriz->transposta[i]);
    free(matriz->transposta);
}

void le_palavra_buscada(char palavra_buscada[], Matriz matriz)
{
    printf("\nInsira a palavra a ser procurada: ");
    fgets(palavra_buscada, matriz.numero_de_colunas, stdin);
    palavra_buscada[strlen(palavra_buscada) - 1] = '\0';
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
        printf("5 - Diagonal principal direta\n");
        printf("6 - Diagonal principal inversa\n");
        printf("7 - Diagonal secundária direta\n");
        printf("8 - Diagonal secundária inversa\n");
        printf("Insira o número de sua opção: ");
        scanf("%d", &opcao_de_busca);
    }
    while(opcao_de_busca < 1 || opcao_de_busca > 8);

    return opcao_de_busca;
}

void inverte_string(char string[], int tamanho)
{
    char auxiliar = ' ';
    int indice_inverso = tamanho - 1;

    for(int i = 0; i < tamanho / 2; i++)
    {
        auxiliar = string[i];
        string[i] = string[indice_inverso];
        string[indice_inverso] = auxiliar;
        indice_inverso--;
    }
}

void calcula_fim_da_palavra(Coordenadas* posicoes, char palavra_buscada[], int tipo_de_busca)
{
    switch(tipo_de_busca)
    {
        case 1:
            posicoes->fim.x = posicoes->inicio.x + strlen(palavra_buscada) - 1;
            posicoes->fim.y = posicoes->inicio.y;
            break;
        case 2:
            posicoes->fim.x = posicoes->inicio.x - strlen(palavra_buscada) + 1;
            posicoes->fim.y = posicoes->inicio.y;
            break;
        case 3:
            posicoes->fim.x = posicoes->inicio.x;
            posicoes->fim.y = posicoes->inicio.y + strlen(palavra_buscada) - 1;
            break;
        case 4:
            posicoes->inicio.y += strlen(palavra_buscada) - 1; 
            posicoes->fim.x = posicoes->inicio.x;
            posicoes->fim.y = posicoes->inicio.y - strlen(palavra_buscada) + 1;
            break;
    }
}

void atualiza_posicao_da_palavra(Matriz* matriz, char* endereco_base, Coordenadas* posicoes, char palavra_buscada[], int tipo_de_busca)
{   
    bool pesquisar_na_transposta = false;

    if(tipo_de_busca == 3 || tipo_de_busca == 4) pesquisar_na_transposta = true;

    if(pesquisar_na_transposta)
    {
        for(int i = 0; i < matriz->numero_de_colunas; i++)
        {
            for(int j = 0; j < matriz->numero_de_linhas; j++)
            {
                if(endereco_base == &matriz->transposta[i][j])
                {
                    posicoes->inicio.x = i + 1;
                    posicoes->inicio.y = j + +1;
                    calcula_fim_da_palavra(posicoes, palavra_buscada, tipo_de_busca);
                }
            }
        }
    }
    else
    {
        for(int i = 0; i < matriz->numero_de_linhas; i++)
        {
            for(int j = 0; j < matriz->numero_de_colunas; j++)
            {
                if(endereco_base == &matriz->matriz[i][j])
                {
                    posicoes->inicio.x = j + 1;
                    posicoes->inicio.y = i + 1;
                    calcula_fim_da_palavra(posicoes, palavra_buscada, tipo_de_busca);
                }
            }
        }
    }
}

void transpoe_matriz(Matriz* matriz)
{
    for(int i = 0; i < matriz->numero_de_linhas; i++)
    {
        for(int j = 0; j < matriz->numero_de_colunas; j++) matriz->transposta[j][i] = matriz->matriz[i][j];
    }
}

void busca_palavra(Matriz* matriz, Coordenadas* posicoes, char palavra_buscada[])
{
    int opcao_de_busca = seleciona_sentido_da_busca();
    char* primeiro_endereco_palavra = NULL;
    bool pesquisar_na_transposta = false;

    switch(opcao_de_busca)
    {
        case 1:
            break;
        case 2:
            inverte_string(palavra_buscada, strlen(palavra_buscada));
            break;
        case 3:
            pesquisar_na_transposta = true;
            break;
        case 4:
            pesquisar_na_transposta = true;
            inverte_string(palavra_buscada, strlen(palavra_buscada));
            break;
    }

    if(pesquisar_na_transposta)
    {
        for(int i = 0; i < matriz->numero_de_colunas; i++)
        {
            primeiro_endereco_palavra = strstr(matriz->transposta[i], palavra_buscada);
            if(primeiro_endereco_palavra != NULL) break;
        }
    }
    else
    {
        for(int i = 0; i < matriz->numero_de_linhas; i++)
        {
            primeiro_endereco_palavra = strstr(matriz->matriz[i], palavra_buscada);
            if(primeiro_endereco_palavra != NULL) break;
        }
    }
    
    if(primeiro_endereco_palavra != NULL) 
    {
        atualiza_posicao_da_palavra(matriz, primeiro_endereco_palavra, posicoes, palavra_buscada, opcao_de_busca);
    }
}
