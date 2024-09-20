/*MATRIZES Faça um programa em C que armazene numa matriz de inteiros (de tamanho m x 6) os seguintes
dados COVID referentes a m municípios:
a. A primeira coluna guarda o código do município;
b. A segunda coluna guarda a quantidade de habitantes do município;
c. A terceira coluna guarda o total de casos confirmados;
d. A quarta coluna guarda o total de óbitos;
e. A quinta coluna guarda a incidência de casos a cada 100 mil habitantes;
f. A sexta coluna guarda a mortalidade a cada 100 mil habitantes.

Exemplo: um município com 283 mil habitantes, 52 mil casos e 850 óbitos, tem uma incidência de 18374
casos por 100 mil habitantes e uma mortalidade de 300 óbitos por 100 mil habitantes.
Faça um programa em C que:
a. Leia e preencha as quatro primeiras colunas da matriz;
b. Calcule e armazene as duas últimas colunas da matriz;
c. Imprima toda a matriz;
d. Mostre qual o código do município que tem a maior mortalidade;
e. Mostre qual o código do município que tem a maior incidência de casos.
Cada um dos itens acima deve ser uma função separada.*/

#include <stdio.h>
#include <stdbool.h>

int decide_numero_linhas(void);
void inicializa_matriz(int num_municipios, int matriz[num_municipios][6]);
void preenche_matriz(int num_municipios, int matriz[num_municipios][6]);
int le_codigo_municipio(void);
int le_qntd_habitantes(void);
int le_casos_confirmados(void);
int le_obitos(void);
int calcula_casos_cem_mil_habitantes(int habitantes, int casos);
int calcula_obitos_cem_mil_habitantes(int habitantes, int obitos);
void imprime_mensagem_confirmacao(void);
void imprime_matriz(int numero_municipios, int matriz[numero_municipios][6]);
int decide_codigo_maior_mortalidade(int numero_municipios, int matriz[numero_municipios][6]);
void imprime_codigo_maior_mortalidade(int numero_municipios, int matriz[numero_municipios][6]);
int decide_codigo_mais_casos(int numero_municipios, int matriz[numero_municipios][6]);
void imprime_codigo_mais_casos(int numero_municipios, int matriz[numero_municipios][6]);
bool garante_codigo_unico(int codigo, int numero_municipios, int matriz[numero_municipios][6]);
int codigo_valido(int numero_municipios, int matriz[numero_municipios][6]);

int main(void)
{
    int num_municipios = decide_numero_linhas();
    int matriz[num_municipios][6];

    inicializa_matriz(num_municipios, matriz);
    preenche_matriz(num_municipios, matriz);
    imprime_matriz(num_municipios, matriz);
    imprime_codigo_maior_mortalidade(num_municipios, matriz);
    imprime_codigo_mais_casos(num_municipios, matriz);
}

int decide_numero_linhas(void)
{
    int num_municipios = 0;

    printf("Quantos municípios serão registrados?\n");
    scanf("%d", &num_municipios);
    
    return num_municipios;
}

void inicializa_matriz(int num_municipios, int matriz[num_municipios][6])
{
    for(int i = 0; i < num_municipios; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            matriz[i][j] = -1;
        }
    }
}

void preenche_matriz(int num_municipios, int matriz[num_municipios][6])
{
    
    for(int i = 0; i < num_municipios; i++)
    {
        matriz[i][0] = codigo_valido(num_municipios, matriz);
        matriz[i][1] = le_qntd_habitantes();
        matriz[i][2] = le_casos_confirmados();
        matriz[i][3] = le_obitos(); 
        matriz[i][4] = calcula_casos_cem_mil_habitantes(matriz[i][1], matriz[i][2]);
        matriz[i][5] = calcula_obitos_cem_mil_habitantes(matriz[i][1], matriz[i][3]);
        imprime_mensagem_confirmacao();
    }
}

int le_codigo_municipio(void)
{
    int codigo = -1;

    printf("Insira o código do município: ");
    scanf("%d", &codigo);

    return codigo;
}

int le_qntd_habitantes(void)
{
    int habitantes = -1;

    printf("Insira o número de habitantes: ");
    scanf("%d", &habitantes);

    return habitantes;
}

int le_casos_confirmados(void)
{
    int casos = -1;

    printf("Insira o número de casos de COVID-19 confirmados: ");
    scanf("%d", &casos);

    return casos;
}

int le_obitos(void)
{
    int obitos = -1;

    printf("Insira o total de óbitos por COVID-19: ");
    scanf("%d", &obitos);

    return obitos;
}

int calcula_casos_cem_mil_habitantes(int habitantes, int casos)
{
    int casos_por_cem_mil = casos / (habitantes / 100000.0);

    return casos_por_cem_mil;
}

int calcula_obitos_cem_mil_habitantes(int habitantes, int obitos)
{
    int obitos_por_cem_mil = obitos / (habitantes / 100000.0);

    return obitos_por_cem_mil;
}

void imprime_mensagem_confirmacao(void)
{
    printf("Município registrado!\n");
}

void imprime_matriz(int numero_municipios, int matriz[numero_municipios][6])
{
    printf(" Código do município | Habitantes | Casos confirmados | Óbitos | Casos/100 mil habitantes | Óbitos/100 mil habitantes\n");

    for(int i = 0; i < numero_municipios; i++)
    {
        for(int j = 0; j < 6; j++)
        {
            printf(" %d ", matriz[i][j]);

            if(j != 5) printf("|");
        }

        printf("\n");
    }
}

int decide_codigo_maior_mortalidade(int numero_municipios, int matriz[numero_municipios][6])
{
    int maior_mortalidade = -1;
    int codigo_maior_mortalidade = -1;

    for(int i = 0; i < numero_municipios; i++)
    {
        if(matriz[i][3] > maior_mortalidade)
        {
            maior_mortalidade = matriz[i][3];
            codigo_maior_mortalidade = matriz[i][0];
        }
    }

    return codigo_maior_mortalidade;
}

void imprime_codigo_maior_mortalidade(int numero_municipios, int matriz[numero_municipios][6])
{
    int codigo_maior_mortalidade = decide_codigo_maior_mortalidade(numero_municipios, matriz);
    printf("Município de maior mortalidade: %d\n", codigo_maior_mortalidade);
}

int decide_codigo_mais_casos(int numero_municipios, int matriz[numero_municipios][6])
{
    int mais_casos = -1;
    int codigo_mais_casos = -1;

    for(int i = 0; i < numero_municipios; i++)
    {
        if(matriz[i][2] > mais_casos)
        {
            mais_casos = matriz[i][2];
            codigo_mais_casos = matriz[i][0];
        }
    }

    return codigo_mais_casos;
}

void imprime_codigo_mais_casos(int numero_municipios, int matriz[numero_municipios][6])
{
    int codigo_mais_casos = decide_codigo_mais_casos(numero_municipios, matriz);
    printf("Município com mais casos: %d\n", codigo_mais_casos);
}

bool garante_codigo_unico(int codigo, int numero_municipios, int matriz[numero_municipios][6])
{
    for(int i = 0; i < numero_municipios; i++)
    {
        if(matriz[i][0] == codigo) return false;
    }

    return true;
}

int codigo_valido(int numero_municipios, int matriz[numero_municipios][6])
{
    bool codigo_unico = false;
    int guarda_codigo = 0;

    while(true)
    {
        guarda_codigo = le_codigo_municipio();
        codigo_unico = garante_codigo_unico(guarda_codigo, numero_municipios, matriz);

        if(codigo_unico) break;

        printf("Código inválido. Esse código já está em uso.\n");
    }

    return guarda_codigo;
}
