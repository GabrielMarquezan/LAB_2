#include "menu.h"

/*1) Abrir restaurante: informar quantidade de mesas (linhas e colunas da matriz) e arrumar as mesas completas.
2) Chegar (grupo de) clientes ao restaurante: implica em ocupar mesa se há disponibilidade ou ir pra fila de espera.
3) Finalizar refeição/liberar mesa: sempre que uma mesa é liberada, a mesa completa é arrumada (4 pratos), clientes
são chamados da fila de espera (se houver) e a quantidade de pratos é ajustada na mesa (tirar pratos excedentes da
mesa, se necessário, e recolocá-los na pilha).
4) Desistir de esperar: sair da fila de espera.
5) Repor pratos: adicionar pratos na pilha.
6) Imprimir pilha de pratos, fila de espera e ocupação das mesas, conforme descrito a seguir:
 Ocupação das mesas (número da mesa e quantidade de pessoas que ocupam a mesa) - o usuário pode pesquisar
por número de mesa ou então consultar todas as mesas;
 Fila de espera (quantos grupos estão na fila de espera, e quantas pessoas aguardam na fila de espera. Por ex:
grupo 1 aguarda por 3 lugares, grupo 2 aguarda por 5 lugares, logo há 2 grupos aguardando, e um total de 8 pessoas
esperam na fila);
 Pilha de pratos (quantos pratos existem na pilha de pratos).*/

void imprime_menu()
{
    printf("Escolha uma opção:\n");
    printf("1 - Abrir restaurante\n");
    printf("2 - Chegar (grupo de) clientes ao restaurante\n");
    printf("3 - Finalizar refeição/liberar mesa\n");
    printf("4 - Desistir de esperar\n");
    printf("5 - Imprimir pilha de pratos\n");
    printf("6 - Imprimir fila de espera\n");
    printf("7 - Imprimir ocupação das mesas\n");
    printf("8 - Sair\n");
    
}

int processa_escolha(Mesa** mesas, Pilha_de_Pratos** pilha, Fila_de_Espera** fila, int linhas, int colunas, bool* restaurante_aberto)
{
    int escolha = 0;

    scanf("%d", &escolha);
    if(escolha < 1 || escolha > 8)
    {
        printf("Escolha inválida. Tente novamente.\n");
        return 1;
    }

    switch (escolha)
    {
    case 1:
        inicializar_restaurante(&mesas, pilha, restaurante_aberto);
        break;
    case 2:
        adiciona_grupo_na_fila(fila);
        break;
    case 3:
        int id_mesa = -2;

        while(id_mesa < 1 || id_mesa > linhas * colunas)
        {
            printf("Informe o número da mesa que deseja liberar (ou -1 para cancelar): ");
            scanf("%d", &id_mesa);

            if(id_mesa == -1) break;
        }
        libera_mesa(fila, pilha, mesas, linhas, colunas, id_mesa);
        ocupa_mesa(fila, mesas, pilha, id_mesa, linhas, colunas);
        break;
    case 4:
        remove_grupo_da_fila(fila);
        break;
    case 5:
        imprime_pilha_de_pratos(*pilha);
        break;
    case 6:
        imprime_fila_de_espera(*fila);
        break;
    case 7:
        imprime_ocupacao_das_mesas(mesas, linhas, colunas);
        break;
    case 8:
        return 0;
    }

    return 1;
}
