#include "mesas.h"

//Ids e comandas são inteiros simples

Mesa** aloca_matriz_de_mesas(int n_linhas, int n_colunas)
{
    Mesa** matriz = (Mesa**) malloc(n_linhas * sizeof(Mesa*));
    if(matriz == NULL)
    {
        printf("Erro ao alocar matriz de mesas.\n\n");
        return NULL;
    }

    for (int i = 0; i < n_linhas; i++)
    {
        matriz[i] = (Mesa*) malloc(n_colunas * sizeof(Mesa));
        if(matriz[i] == NULL)
        {
            printf("Erro ao alocar linha %d matriz de mesas.\n\n", i);
            desaloca_matriz_de_mesas(matriz, i);
            return NULL;
        }
    }
    return matriz;
}

void desaloca_matriz_de_mesas(Mesa** matriz, int n_linhas)
{
    if(matriz == NULL) 
    {
        printf("Matriz de mesas está vazia. Impossível desalocar!\n\n");
        return;
    }

    for(int i = 0; i < n_linhas; i++)
    {
        if(matriz[i] == NULL)
        {
            printf("Linha %d da matriz de mesas está vazia. Impossível desalocar!\n\n", i);
            return;
        }
        free(matriz[i]);
    }
    free(matriz);
}

Pilha_de_Pratos* cria_pilha_vazia()
{
    return NULL;
}

void inicializa_pilha_de_pratos(Pilha_de_Pratos** pilha, int numero_de_pratos)
{
    Pilha_de_Pratos* novo_no;

    for(int i = 1; i <= numero_de_pratos; i++)
    {
        novo_no = (Pilha_de_Pratos*) malloc(sizeof(Pilha_de_Pratos));
        if(novo_no == NULL)
        {
            printf("Erro ao alocar novo espaço na pilha (inicialização).\n\n");
            return;
        }

        novo_no->prato = (Prato*) malloc(sizeof(Prato));
        if(novo_no->prato == NULL)
        {
            printf("Erro ao alocar prato %d.\n\n", i);
            return;
        }

        novo_no->prato->id = i;
        novo_no->proximo_prato = *pilha;
        *pilha = novo_no;
    }
}

void desaloca_pilha_de_pratos(Pilha_de_Pratos** pilha)
{
    Pilha_de_Pratos* auxiliar;
    while(*pilha != NULL)
    {
        auxiliar = *pilha;
        *pilha = (*pilha)->proximo_prato;
        free(auxiliar->prato);
        free(auxiliar);
    }
}

void empilha_prato(Pilha_de_Pratos** pilha, Prato* prato)
{
    Pilha_de_Pratos* novo_no = (Pilha_de_Pratos*) malloc(sizeof(Pilha_de_Pratos));
    if(novo_no == NULL)
    {
        printf("Erro ao alocar novo espaço na pilha.\n\n");
        return;
    }
    novo_no->prato = prato;
    novo_no->proximo_prato = *pilha;
    *pilha = novo_no;
}

Prato* desempilha_prato(Pilha_de_Pratos** pilha)
{ 
    if(*pilha == NULL)
    {
        printf("Pilha de pratos vazia. Impossível desempilhar.\n\n");
        return NULL;
    }
    //Retorna o prato desempilhado
    Pilha_de_Pratos* auxiliar = *pilha;
    Prato* prato = auxiliar->prato;
    *pilha = auxiliar->proximo_prato;
    free(auxiliar);
    return prato;
}

void inicializa_mesas(Mesa** mesas, Pilha_de_Pratos** pilha, int n_linhas, int n_colunas)
{
    if(mesas == NULL)
    {
        printf("Matriz de mesas está vazia. Impossível inicializar mesas.\n\n");
        return;
    }

    //Necessita que a pilha de pratos esteja inicializada
    if(*pilha == NULL)
    {
        printf("Pilha de pratos não inicializada. Impossível inicializar mesas.\n\n");
        return;
    }

    int contador = 1;

    for (int i = 0; i < n_linhas; i++)
    {
        if(mesas[i] == NULL)
        {
            printf("Linha %d da matriz de mesas está vazia. Impossível inicializar mesas.\n\n", i);
            return;
        }

        for (int j = 0; j < n_colunas; j++)
        {
            mesas[i][j].id = contador;
            mesas[i][j].ocupada = false;
            mesas[i][j].lugares_ocupados = 0;
            mesas[i][j].comanda = contador;

            for(int k = 0; k < MAX_LUGARES_POR_MESA; k++) 
            {
                mesas[i][j].pratos_utilizados[k] = desempilha_prato(pilha);
            }
            contador++;
        }
    }
}

Fila_de_Espera* cria_fila_de_espera()
{
    return NULL;
}

void desaloca_fila_de_espera(Fila_de_Espera** fila)
{
    if(*fila == NULL) return;

    Fila_de_Espera* auxiliar;
    while(*fila != NULL)
    {
        auxiliar = *fila;
        *fila = (*fila)->proximo_grupo;
        free(auxiliar);
    }
}

void adiciona_grupo_na_fila(Fila_de_Espera** fila)
{
    Fila_de_Espera* novo_grupo = (Fila_de_Espera*) malloc(sizeof(Fila_de_Espera));
    if(novo_grupo == NULL)
    {
        printf("Erro ao alocar novo espaço na fila de espera.\n\n");
        return;
    }

    Fila_de_Espera* grupo_atual = *fila;
    int tamanho_do_grupo = -1;

    while(tamanho_do_grupo < 1)
    {
        printf("Qual é o tamanho do grupo que chegou (-1 para cancelar)?\n");
        printf("Tamanho do grupo: ");
        scanf("%d", &tamanho_do_grupo);
        if(tamanho_do_grupo == -1) return;
        else if(tamanho_do_grupo < 1) printf("Tamanho inválido. Tente novamente.\n\n");
    }

    if(grupo_atual == NULL) novo_grupo->posicao = 1;
    else novo_grupo->posicao = grupo_atual->posicao + 1;

    novo_grupo->tamanho_do_grupo = tamanho_do_grupo;
    novo_grupo->proximo_grupo = grupo_atual;
    *fila = novo_grupo;

    printf("Grupo de %d pessoas adicionado à fila de espera.\n\n", tamanho_do_grupo);
}

int remove_grupo_da_fila(Fila_de_Espera** fila, bool desistir)
{
    if(*fila == NULL)
    {
        printf("\nFila de espera está vazia. Impossível remover grupo.\n\n");
        return -1;
    }

    //Retorna o número de pessoas que estavam no grupo removido
    Fila_de_Espera* grupo_anterior = NULL;

    for(Fila_de_Espera* grupo = *fila; grupo != NULL; grupo = grupo->proximo_grupo)
    {
        if(grupo->proximo_grupo == NULL)
        {   
            if(grupo->tamanho_do_grupo <= MAX_LUGARES_POR_MESA || desistir)
            {
                if(grupo_anterior != NULL) 
                {
                    grupo_anterior->proximo_grupo = NULL;
                    for(Fila_de_Espera* aux = *fila; aux != NULL; aux = aux->proximo_grupo) aux->posicao--;
                }
                else *fila = NULL;

                if(desistir) printf("Grupo de %d pessoas desistiu da fila.\n\n", grupo->tamanho_do_grupo);
                else printf("Grupo de %d pessoas foi chamado para a mesa.\n\n", grupo->tamanho_do_grupo);

                int numero_de_pessoas = grupo->tamanho_do_grupo;
                free(grupo);
                return numero_de_pessoas;
            }
            else
            {
                grupo->tamanho_do_grupo -= MAX_LUGARES_POR_MESA;
                return MAX_LUGARES_POR_MESA;
            }
        }
        grupo_anterior = grupo;
    }
}

void inicializar_restaurante(Mesa*** mesas, Pilha_de_Pratos** pilha, int* linhas, int* colunas, bool* restaurante_aberto)
{
    printf("\n");

    if(*restaurante_aberto)
    {
        printf("Restaurante já está aberto.\n\n");
        return;
    }

    while(*linhas < 1 || *colunas < 1)
    {
        printf("Informe número de linhas de mesas : ");
        scanf("%d", linhas);
        printf("Informe número de colunas de mesas : ");
        scanf("%d", colunas);
    }

    *mesas = aloca_matriz_de_mesas(*linhas, *colunas);
    inicializa_pilha_de_pratos(pilha, *linhas * *colunas * MAX_LUGARES_POR_MESA);
    inicializa_mesas(*mesas, pilha, *linhas, *colunas);

    printf("Restaurante aberto com sucesso!\n\n");
    *restaurante_aberto = true;
}

Mesa* busca_mesa(Mesa** mesas, int linhas, int colunas, int id_mesa)
{
    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            if(mesas[i][j].id == id_mesa)
            {
                return &mesas[i][j];
            }
        }
    }
    return NULL;
}

Mesa* acha_mesa_livre(Mesa** mesas, int linhas, int colunas)
{
    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++) if(!mesas[i][j].ocupada) return &mesas[i][j];
    }
    return NULL;
}

void arruma_mesa(Mesa* mesa, Pilha_de_Pratos** pilha)
{
    if(mesa->ocupada) printf("Mesa %d está ocupada. Não é possível arrumá-la.\n\n", mesa->id);
    else
    {
        Prato* pratos[MAX_LUGARES_POR_MESA];

        //Tira os pratos usados da mesa
        for(int k = 0; k < mesa->lugares_ocupados; k++) empilha_prato(pilha, mesa->pratos_utilizados[k]);
        //Coloca pratos novos na mesa
        for(int i = 0; i < MAX_LUGARES_POR_MESA; i++) 
        {
            pratos[i] = desempilha_prato(pilha);
            mesa->pratos_utilizados[i] = pratos[i];
        }
        
        printf("Mesa %d arrumada com sucesso!\n\n", mesa->id);
    }
}

void libera_mesa(Fila_de_Espera** fila, Pilha_de_Pratos** pilha, Mesa** mesas, int linhas, int colunas, int id_mesa)
{
    Mesa* mesa = busca_mesa(mesas, linhas, colunas, id_mesa);
    if(mesa == NULL)
    {
        printf("Mesa %d não encontrada.\n\n", id_mesa);
        return;
    }

    if(mesa->ocupada)
    {
        mesa->ocupada = false;
        arruma_mesa(mesa, pilha);
        mesa->lugares_ocupados = 0;
        printf("Mesa %d liberada com sucesso!\n\n", id_mesa);
    }
    else printf("Mesa %d já está livre.\n\n", id_mesa);
}

Fila_de_Espera* retorna_primeiro_grupo_da_fila(Fila_de_Espera* fila)
{
    for(Fila_de_Espera* grupo = fila; grupo != NULL; grupo = grupo->proximo_grupo)
    {
        if(grupo->proximo_grupo == NULL) return grupo;
    }
}

void ocupa_mesa(Fila_de_Espera** fila, Mesa** mesas, Pilha_de_Pratos** pilha, int linhas, int colunas)
{
    Mesa* mesa = acha_mesa_livre(mesas, linhas, colunas);
    Fila_de_Espera* primeiro_grupo = retorna_primeiro_grupo_da_fila(*fila);

    while(primeiro_grupo != NULL && mesa != NULL) 
    {
        int numero_de_pessoas = remove_grupo_da_fila(fila, false);
        if(numero_de_pessoas == -1) return;

        mesa->lugares_ocupados = numero_de_pessoas;
        mesa->ocupada = true;
        for(int i = mesa->lugares_ocupados; i < MAX_LUGARES_POR_MESA; i++)
        {
            empilha_prato(pilha, mesa->pratos_utilizados[i]);
            mesa->pratos_utilizados[i] = NULL;
        }

        printf("Mesa %d ocupada com sucesso!\n\n", mesa->id);
        primeiro_grupo = retorna_primeiro_grupo_da_fila(*fila);
        mesa = acha_mesa_livre(mesas, linhas, colunas);
    }

    if(primeiro_grupo == NULL) printf("Fila de espera está vazia.\n\n");
    if(mesa == NULL) printf("Não há mesa livre para ocupar!\n\n");
}

void imprime_pilha_de_pratos(Pilha_de_Pratos* pilha)
{
    if(pilha == NULL)
    {
        printf("\nPilha vazia!\n\n");
        return;
    }

    for(Pilha_de_Pratos* atual = pilha; atual != NULL; atual = atual->proximo_prato)
    {
        if(atual == pilha) printf("\nTopo da pilha: prato %d\n", atual->prato->id);
        else if(atual->proximo_prato == NULL) printf("Térreo da pilha: prato %d\n\n", atual->prato->id);
        else if(atual != NULL) printf("Prato %d\n", atual->prato->id);
    }
}

void imprime_fila_de_espera(Fila_de_Espera* fila)
{
    printf("\n\n");
    for(Fila_de_Espera* atual = fila; atual != NULL; atual = atual->proximo_grupo) printf("%d pessoas - %d° grupo da fila\n", atual->tamanho_do_grupo, atual->posicao);
    if(fila == NULL) printf("Fila de espera vazia!\n");
    printf("\n");
}

void imprime_ocupacao_das_mesas(Mesa** mesas, int linhas, int colunas)
{
    printf("\n");
    if(mesas == NULL)
    {
        printf("Matriz de mesas está vazia. Impossível imprimir ocupação.\n\n");
        return;
    }

    for(int i = 0; i < linhas; i++)
    {
        for(int j = 0; j < colunas; j++)
        {
            printf("Número da mesa: %d\n", mesas[i][j].id);
            if(mesas[i][j].ocupada)
            {
                printf("Mesa ocupada: sim\n");
                printf("Lugares ocupados: %d\n", mesas[i][j].lugares_ocupados);
            }
            else printf("Mesa ocupada: não\n");
            printf("Número da comanda: %d\n", mesas[i][j].comanda);
            printf("Id dos pratos na mesa: ");
            for(int k = 0; k < MAX_LUGARES_POR_MESA; k++)
            {
                if(mesas[i][j].pratos_utilizados[k] != NULL) printf("%d", mesas[i][j].pratos_utilizados[k]->id);
                else
                {
                    printf("Nenhum prato ocupado!\n");
                    break;
                }

                if(mesas[i][j].pratos_utilizados[k+1] != NULL && k+1 < MAX_LUGARES_POR_MESA) printf(", ");
                else break;
            }
            printf("\n\n");
        }
    }
}

void retira_pratos_da_mesa_sem_desocupar(Mesa* mesa, Pilha_de_Pratos** pilha)
{
    int numero_de_pratos = -1;

    printf("Informe quantos pratos deseja retirar: ");
    scanf("%d", &numero_de_pratos);

    if(numero_de_pratos < 1 || numero_de_pratos > mesa->lugares_ocupados)
    {
        printf("Número de pratos inválido. Tente novamente.\n\n");
        return;
    }

    for(int i = mesa->lugares_ocupados - numero_de_pratos; i < mesa->lugares_ocupados; i++)
    {
        if(mesa->pratos_utilizados[i] == NULL)
        {
            printf("Erro ao retirar pratos da mesa.\n\n");
            return;
        }

        empilha_prato(pilha, mesa->pratos_utilizados[i]);
        mesa->pratos_utilizados[i] = NULL;
    }

    printf("Pratos retirados com sucesso!\n\n");	
}
