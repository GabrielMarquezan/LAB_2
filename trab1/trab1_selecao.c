/*
Considere uma disciplina que adota o seguinte critério de aprovação: os alunos fazem duas provas
(P1 e P2) iniciais; se a média nas duas provas for maior ou igual a 5.0, e se nenhuma das duas notas for inferior
a 3.0, o aluno passa direto. Caso contrário, o aluno faz uma terceira prova (P3) e a média é calculada
considerando-se a terceira nota e a maior das notas entre P1 e P2. Neste caso, o aluno é aprovado se a média
final for maior ou igual a 5.0.
Escreva um programa em C que leia inicialmente as duas notas de um aluno, fornecidas pelo usuário
via teclado. Se as notas não forem suficientes para o aluno passar direto, o programa deve capturar a nota da
terceira prova, também fornecida via teclado. Como saída, o programa deve imprimir a média final do aluno,
seguida da mensagem “Aprovado” ou “Reprovado”.
*/

#include <stdio.h>
#include <stdbool.h>

void le_notas_iniciais(float notas[]);
bool verifica_se_passou_direto(float notas[]);
bool verifica_se_maior_que_tres(float nota_1, float nota_2);
bool verifica_media_maior_que_cinco(float nota_1, float nota_2);
void imprime_aviso_passou_direto_ou_nao(bool passou_direto);
void le_nota_p3(float notas[]);
float maior_nota_iniciais(float notas[]);
bool verifica_passou_p3(float notas[]);
void imprime_aprovado_p3_ou_nao(bool passou_p3);
void imprime_media_final(float media);
float calcula_media_final(float notas[], bool passou_direto);
void media_final(float notas[], bool passou_direto);


int main(void)
{
    float notas[4] = {0, 0, 0, 0};

    bool passou_direto = false;
    bool passou_p3 = false;

    le_notas_iniciais(notas);
    
    passou_direto = verifica_se_passou_direto(notas);
    imprime_aviso_passou_direto_ou_nao(passou_direto);

    if(!passou_direto)
    {
        le_nota_p3(notas);
        passou_p3 = verifica_passou_p3(notas);
        imprime_aprovado_p3_ou_nao(passou_p3);
    }

    media_final(notas, passou_direto);
}

void le_notas_iniciais(float notas[])
{
    printf("Digite a nota da p1 (utilize . como separador decimal): ");
    scanf("%f", &notas[0]);

    printf("Digite a nota da p2 (utilize . como separador decimal): ");
    scanf("%f", &notas[1]);
}

bool verifica_se_passou_direto(float notas[])
{
    bool criterio_tres = verifica_se_maior_que_tres(notas[0], notas[1]);
    bool criterio_media = verifica_media_maior_que_cinco(notas[0], notas[1]);

    if(criterio_tres && criterio_media)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool verifica_se_maior_que_tres(float nota_1, float nota_2)
{
    if(nota_1 >= 3 && nota_2 >= 3)
    {
        return true;
    }
    else
    {
        return false;
    }
}

bool verifica_media_maior_que_cinco(float nota_1, float nota_2)
{
    float media = (nota_1 + nota_2) / 2;

    if(media >= 5)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void imprime_aviso_passou_direto_ou_nao(bool passou_direto)
{
    if(passou_direto)
    {
        printf("Parabéns! Você foi aprovado sem p3.\n");
    }
    else
    {
        printf("Infelizmente, sua nota não foi suficiente. Deve fazer a p3.\n");
    }
}

void le_nota_p3(float notas[])
{
    printf("Digite a nota da p3 (utilize . como separador decimal): ");
    scanf("%f", &notas[2]);
}

float maior_nota_iniciais(float notas[])
{
    if(notas[0] > notas[1])
    {
        return notas[0];
    }
    else
    {
        return notas[1];
    }
}

bool verifica_passou_p3(float notas[])
{
    notas[3] = maior_nota_iniciais(notas);

    bool criterio_media = verifica_media_maior_que_cinco(notas[3], notas[2]);

    if(criterio_media)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void imprime_aprovado_p3_ou_nao(bool passou_p3)
{
    if(passou_p3)
    {
        printf("Parabéns! Você foi aprovado na p3!");
    }
    else
    {
        printf("Infelizmente, você não passou na p3.");
    }
}

void imprime_media_final(float media)
{
    printf("Sua média final: %.2f\n", media);
}

float calcula_media_final(float notas[], bool passou_direto)
{
    float media = 0;

    if(passou_direto)
    {
        media = (notas[0] + notas[1]) / 2;
    }
    else
    {
        media = (notas[2] + notas[3]) / 2;
    }

    return media;
}

void media_final(float notas[], bool passou_direto)
{
    float media = calcula_media_final(notas, passou_direto);
    imprime_media_final(media); 
}
