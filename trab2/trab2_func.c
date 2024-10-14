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
    getchar(); //Captura o ENTER digitado por último para que o fgets() funcione corretamente
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
    for(int i = 0; i < matriz->numero_de_linhas; i++) matriz->matriz[i][matriz->numero_de_colunas] = '\0';
}

void preenche_matriz(Matriz* matriz)
{   
    /*texto para matriz tem um tamanho arbitrariamente maior que o alocado para garantir que 
    nada seja truncado pela existência de espaços na entrada do usuário*/
    int tamanho_do_texto_para_matriz = matriz->numero_de_linhas * matriz->numero_de_colunas * 1.5;
    char texto_para_matriz[tamanho_do_texto_para_matriz];
    int contador = 0;

    texto_pronto_para_matriz(texto_para_matriz, tamanho_do_texto_para_matriz);

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

void deixa_matriz_pronta(Matriz* matriz)
{
    le_dimensoes_matriz(matriz);
    matriz->matriz = aloca_matriz(matriz->numero_de_linhas, matriz->numero_de_colunas);
    matriz->transposta = aloca_matriz(matriz->numero_de_colunas, matriz->numero_de_linhas);
    inicializa_matriz(matriz);
    preenche_matriz(matriz);
    transpoe_matriz(matriz);
}

void imprime_matriz(char** matriz, int linhas, int colunas)
{
    printf("\n    ");

    //Imprime o índice das colunas
    for(int i = 0; i < colunas; i++)
    {
        if(i < 9) printf("| 0%d ", i + 1);
        else printf("| %d ", i + 1);
    }

    printf("|\n");

    for(int i = 0; i < linhas; i++)
    {
        for(int i = 0; i < 5 * colunas + 5; i++) printf("-"); //Divide as linhas
        
        //Imprime o índice das linhas
        if(i < 9) printf("\n 0%d ", i + 1); 
        else printf("\n %d ", i + 1);

        //Imprime o conteúdo da matriz, garantindo que sejam letras e não lixo eletrônico
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

void inicializa_vetor_de_char(char vetor[], int tamanho)
{
    for(int i = 0; i < tamanho - 1; i++) vetor[i] = ' ';
    vetor[tamanho - 1] = '\0';
}

void le_palavra_buscada(char palavra_buscada[], Matriz matriz)
{
    printf("\nInsira a palavra a ser procurada: "); 
    scanf("%s", palavra_buscada);
    palavra_buscada[strlen(palavra_buscada) - 1] = '\0'; //Substitui o '\n' que fica no final por '\0'
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
    switch(tipo_de_busca) //Altera a posição final com base no tipo de busca
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
                    posicoes->inicio.y = j + 1;
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

void transpoe_matriz(Matriz* matriz) //Cria a transposta da matriz
{
    for(int i = 0; i < matriz->numero_de_linhas; i++)
    {
        for(int j = 0; j < matriz->numero_de_colunas; j++) matriz->transposta[j][i] = matriz->matriz[i][j];
    }
}

void busca_diagonal_principal(Matriz* matriz, Coordenadas* posicoes, char palavra_buscada[], bool inversa)
{
    int tamanho_da_palavra = strlen(palavra_buscada);
    bool achou_palavra = false;
    int inicio_linha = -1, inicio_coluna = -1;
    int fim_linha = -1, fim_coluna = -1;

    for(int i = 0; i <= matriz->numero_de_linhas - tamanho_da_palavra; i++)
    {
        for(int j = 0; j <= matriz->numero_de_colunas - tamanho_da_palavra; j++)
        {
            for(int k = 0; k < tamanho_da_palavra; k++) //k é a variável que vai fazer o caminho da diagonal
            {
                if(matriz->matriz[i+k][j+k] == palavra_buscada[k])
                {
                    achou_palavra = true;
                    inicio_linha = i;
                    inicio_coluna = j;
                    fim_linha = i+k;
                    fim_coluna = j+k;
                }
                else
                {
                    achou_palavra = false;
                    break;
                }
            }
            
            if(achou_palavra) break;
        }

        if(achou_palavra) break;
    }

    if(achou_palavra && inversa) //Sempre adicionando +1 para que faça sentido no print final
    {
        posicoes->inicio.y = fim_linha + 1, posicoes->inicio.x = fim_coluna + 1;
        posicoes->fim.y = inicio_linha + 1, posicoes->fim.x = inicio_coluna + 1;
    }
    else if(achou_palavra) //Só inverte inicio e fim
    {
        posicoes->inicio.y = inicio_linha + 1, posicoes->inicio.x = inicio_coluna + 1;
        posicoes->fim.y = fim_linha + 1, posicoes->fim.x = fim_coluna + 1;
    }
}

void busca_diagonal_secundaria(Matriz* matriz, Coordenadas* posicoes, char palavra_buscada[], bool inversa)
{
    int tamanho_da_palavra = strlen(palavra_buscada);
    bool achou_palavra = false;
    int inicio_linha = -1, inicio_coluna = -1;
    int fim_linha = -1, fim_coluna = -1;

    for(int i = 0; i <= matriz->numero_de_linhas - tamanho_da_palavra; i++) //Indo para baixo e para a esquerda
    {
        for(int j = matriz->numero_de_colunas - 1; j >= tamanho_da_palavra; j--)
        {
            for(int k = 0; k < tamanho_da_palavra; k++) //k é a variável que vai fazer o caminho da diagonal
            {
                if(matriz->matriz[i+k][j-k] == palavra_buscada[k])
                {
                    achou_palavra = true;
                    inicio_linha = i;
                    inicio_coluna = j;
                    fim_linha = i+k;
                    fim_coluna = j-k;
                }
                else
                {
                    achou_palavra = false;
                    break;
                }
            }

            if(achou_palavra) break;  
        }

        if(achou_palavra) break;
    }

    if(achou_palavra && inversa) //Sempre adicionando +1 para que faça sentido no print final
    {
        posicoes->inicio.y = fim_linha + 1, posicoes->inicio.x = fim_coluna + 1;
        posicoes->fim.y = inicio_linha + 1, posicoes->fim.x = inicio_coluna + 1;
    }
    else if(achou_palavra) //Só inverte inicio e fim
    {
        posicoes->inicio.y = inicio_linha + 1, posicoes->inicio.x = inicio_coluna + 1;
        posicoes->fim.y = fim_linha + 1, posicoes->fim.x = fim_coluna + 1;
    }
}

void busca_palavra(Matriz* matriz, Coordenadas* posicoes, char palavra_buscada[])
{
    int opcao_de_busca = seleciona_sentido_da_busca();
    char* primeiro_endereco_palavra = NULL;
    //Flags de pesquisa
    bool pesquisar_na_transposta = false, pesquisa_inversa = false;
    bool pesquisa_diagonal_principal = false, pesquisa_diagonal_secundaria = false;

    if(opcao_de_busca % 2 == 0)
    {
        inverte_string(palavra_buscada, strlen(palavra_buscada));
        pesquisa_inversa = true;
    }

    if(opcao_de_busca == 3 || opcao_de_busca == 4) pesquisar_na_transposta = true;
    else if(opcao_de_busca == 5 || opcao_de_busca == 6) pesquisa_diagonal_principal = true;
    else if(opcao_de_busca == 7 || opcao_de_busca == 8) pesquisa_diagonal_secundaria = true;

    //Pesquisas diagonais são separadas pois não podem ser feitas usando transformações da matriz
    if(pesquisa_diagonal_principal) busca_diagonal_principal(matriz, posicoes, palavra_buscada, pesquisa_inversa);
    else if(pesquisa_diagonal_secundaria) busca_diagonal_secundaria(matriz, posicoes, palavra_buscada, pesquisa_inversa);
    else
    {
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
        
        if(primeiro_endereco_palavra != NULL) atualiza_posicao_da_palavra(matriz, primeiro_endereco_palavra, posicoes, palavra_buscada, opcao_de_busca);
    }
}

void imprime_posicoes_palavra(Coordenadas posicoes)
{
    if(posicoes.inicio.x == -1) printf("\nPalavra não encontrada!\n\n");
    else
    {
        printf("\nLinha do início: %d\n", posicoes.inicio.y);
        printf("Coluna do início: %d\n", posicoes.inicio.x);
        printf("Linha do fim: %d\n", posicoes.fim.y);
        printf("Coluna do fim: %d\n", posicoes.fim.x);
    }
}

bool deseja_continuar_jogando(void)
{
    char escolha = ' ';

    getchar(); //Pega o \n

    while(true)
    {
        printf("\nVocê deseja continuar jogando?\n");
        printf("Sim: digite [Y]\n");
        printf("Não: digite [N]\n");
        printf("Insira sua resposta: ");  
        scanf("%c", &escolha);

        if(escolha == 'N' || escolha == 'n') return false;
        else if(escolha == 'Y' || escolha == 'y') return true;
    }
}
