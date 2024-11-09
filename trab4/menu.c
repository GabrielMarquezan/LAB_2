#include "menu.h"

void imprime_menu()
{
    printf("\t\tMENU\n");
    printf("1 - Abrir restaurante\n");
    printf("2 - Clientes chegaram!\n");
    printf("3 - Finalizar refeição/liberar mesa\n");
    printf("4 - Retirar pratos da mesa (não libera mesa)\n");
    printf("5 - Desistir de esperar\n");
    printf("6 - Imprimir pilha de pratos\n");
    printf("7 - Imprimir fila de espera\n");
    printf("8 - Imprimir ocupação das mesas\n");
    printf("9 - Sair\n");
    printf("Escolha uma opção: ");
    
}

int processa_escolha(Mesa*** mesas, Pilha_de_Pratos** pilha, Fila_de_Espera** fila, int* linhas, int* colunas, bool* restaurante_aberto)
{
    int escolha = 0;
    int id_mesa = -2;

    scanf("%d", &escolha);
    if(escolha < 1 || escolha > 9)
    {
        printf("Escolha inválida. Tente novamente.\n\n");
        return 1;
    }

    switch (escolha)
    {
    case 1:
        inicializar_restaurante(mesas, pilha, linhas, colunas,  restaurante_aberto);
        break;
    case 2:
        adiciona_grupo_na_fila(fila);
        ocupa_mesa(fila, *mesas, pilha, *linhas, *colunas);
        break;
    case 3:
        while(id_mesa < 1 || id_mesa > (*linhas) * (*colunas))
        {
            printf("Informe o número da mesa que deseja liberar (ou -1 para cancelar): ");
            scanf("%d", &id_mesa);

            if(id_mesa == -1) return 1;
        }
        libera_mesa(fila, pilha, *mesas, *linhas, *colunas, id_mesa);
        ocupa_mesa(fila, *mesas, pilha, *linhas, *colunas);
        break;
    case 4:
        printf("Informe o id da mesa da qual deseja retirar pratos: ");
        scanf("%d", &id_mesa);

        Mesa* mesa = busca_mesa(*mesas, *linhas, *colunas, id_mesa);
        if(mesa == NULL) 
        {
            printf("Mesa não encontrada.\n\n");
            break;
        }
        retira_pratos_da_mesa_sem_desocupar(mesa, pilha);
        break;
    case 5:
        remove_grupo_da_fila(fila, true);
        break;
    case 6:
        imprime_pilha_de_pratos(*pilha);
        break;
    case 7:
        imprime_fila_de_espera(*fila);
        break;
    case 8:
        imprime_ocupacao_das_mesas(*mesas, *linhas, *colunas);
        break;
    case 9:
        return 0;
    }

    return 1;
}
