#include "mesas.h"
#include "menu.h"

int main()
{
    Mesa** mesas = NULL;
    Pilha_de_Pratos* pilha = NULL;
    Fila_de_Espera* fila = NULL;
    bool restaurante_aberto = false;
    int linhas = 0, colunas = 0;

    while(true)
    {
        imprime_menu();
        if(processa_escolha(&mesas, &pilha, &fila, &linhas, &colunas, &restaurante_aberto) == 0) break;
    }

    desaloca_matriz_de_mesas(mesas, linhas);
    desaloca_pilha_de_pratos(&pilha);
    desaloca_fila_de_espera(&fila);
}
