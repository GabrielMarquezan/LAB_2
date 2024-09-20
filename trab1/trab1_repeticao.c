/*Faça um programa em C que leia vários conjuntos de três valores reais e mostre para cada
conjunto: sua soma, seu produto e sua média. O programa encerra quando não entrar um conjunto com seus
valores em ordem crescente.*/

#include <stdio.h>
#include <stdbool.h>

void le_numeros_iniciais(float conjunto[]);
void le_numero_final(float conjunto[]);
bool verifica_ordem_crescente(float numero_1, float numero_2);
void resultado_final(float conjunto[]);

int main(void)
{
    float conjunto[3] = {0, 0, 0};
    bool ordem_correta = true;

    while(ordem_correta)
    {
        le_numeros_iniciais(conjunto);
        ordem_correta = verifica_ordem_crescente(conjunto[0], conjunto[1]);

        if(!ordem_correta) break;

        le_numero_final(conjunto);

        ordem_correta = verifica_ordem_crescente(conjunto[1], conjunto[2]);

        if(!ordem_correta) break;

        resultado_final(conjunto);
    }

    printf("Insira os números em ordem crescente!\n");
}

void le_numeros_iniciais(float conjunto[])
{
    printf("Digite o primeiro número (utilize . como separador decimal): ");
    scanf("%f", &conjunto[0]);

    printf("Digite o segundo número (utilize o . como separador decimal): ");
    scanf("%f", &conjunto[1]);
}

void le_numero_final(float conjunto[])
{
    printf("Digite o terceiro número (utilize . como separador decimal): ");
    scanf("%f", &conjunto[2]);
}

bool verifica_ordem_crescente(float numero_1, float numero_2)
{
    if(numero_1 < numero_2)
    {
        return true;
    }
    else
    {
        return false;
    }
}

void resultado_final(float conjunto[])
{
    float soma = conjunto[0] + conjunto[1] + conjunto[2];
    float produto = conjunto[0] * conjunto[1] * conjunto[2];

    printf("A soma do conjunto é %.2f\n", soma);
    printf("O produto do conjunto é %.2f\n", produto);
    printf("A média do conjunto é %.2f\n", soma / 3);
}
