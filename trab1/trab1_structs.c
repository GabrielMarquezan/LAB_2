/*Em uma pesquisa de campo, uma editora solicitou os seguintes dados para os entrevistados: idade
e quantidade de livros que leu no ano de 2023. Faça um programa que leia os dados de 5 usuários. Depois,
calcule e imprima:
a. A quantidade total de livros lidos pelos entrevistados menores de 18 anos;
b. A média de livros lidos pelos entrevistados.
Deve ser usada a seguinte struct:
struct usuario
{
int idade;
int qtdade;
};
typedef struct usuario Usuario;

Os dados devem ser armazenados em um vetor de usuários. O programa deve ser estruturado nas seguintes
funções:

void leVetor (int tamanho, Usuario* vet);

//esta funcao recebe o tamanho do vetor e o endereço do primeiro elemento do vetor; preenche o vetor com
dados digitados pelo usuário

int calculaQtidadeLivros (int tamanho, Usuario* vet);

// esta função recebe o tamanho do vetor e o endereco do primeiro elemento do vetor; calcula a quantidade total
de livros lidos pelos entrevistados menores de 18 anos, e retorna esta quantidade para o main

float calculaMedia (int tamanho, Usuario* vet);

// esta função recebe o tamanho do vetor e o endereco do primeiro elemento do vetor; calcula a média de livros
lidos pelos entrevistados e retorna esta quantidade para o main.

Ao final, o main mostra na tela os valores calculados.*/

#include <stdio.h>

typedef struct
{
    int idade;
    int qntd_livros_lidos;
} Usuario;

void leVetor(int tamanho, Usuario* vet);
int le_idade(int numero_usuario);
int le_qntd_livros_todos(void);
int calculaQtidadeLivros (int tamanho, Usuario* vet);
float calculaMedia (int tamanho, Usuario* vet);

int main(void)
{
    Usuario vetor_usuarios[5];
    /*Acredito que não há necessidade de transformar em ponteiro, mas fiz isso para 
    deixar explícito que é o primeiro endereço sendo passado*/
    Usuario* ponteiro = &vetor_usuarios[0];
    int livros_menores18 = 0;
    float media_livros = 0;

    leVetor(5, ponteiro);
    livros_menores18 = calculaQtidadeLivros(5, ponteiro);
    media_livros = calculaMedia(5, ponteiro);

    printf("Os usuário menores de idade leram, no total, %d livros\n", livros_menores18);
    printf("A média de livros lidos por todos os usuários foi %.2f\n", media_livros);
}

int le_idade(int numero_usuario)
{
    int idade = -1;

    printf("Insira a idade do %d° usuário: ", numero_usuario);
    scanf("%d", &idade);

    return idade;
}

int le_qntd_livros_todos(void)
{   
    int livros_lidos = -1;

    printf("E quantos livros foram lidos por ele (a)?\n");
    scanf("%d", &livros_lidos);

    return livros_lidos;
}

void leVetor(int tamanho, Usuario* vet)
{
    for(int i = 0; i < tamanho; i++)
    {
        vet[i].idade = le_idade(i + 1);
        vet[i].qntd_livros_lidos = le_qntd_livros_todos();
    }
}

int calculaQtidadeLivros (int tamanho, Usuario* vet)
{
    int total_livros_menores18 = 0;

    for(int i = 0; i < tamanho; i++)
    {
        if(vet[i].idade < 18)
        {
            total_livros_menores18 += vet[i].qntd_livros_lidos;
        }
    }

    return total_livros_menores18;
}

float calculaMedia (int tamanho, Usuario* vet)
{
    int total_livros = 0;
    float media = 0.0;

    for(int i = 0; i < tamanho; i++) 
    {
        total_livros += vet[i].qntd_livros_lidos;
    }

    media = total_livros / (float) tamanho;

    return media;
}
