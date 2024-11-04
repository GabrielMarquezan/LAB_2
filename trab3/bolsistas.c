#include "bolsistas.h"

void* cria_nova_lista(){
    return NULL;
}

char* inicializa_nomes(){
    char* nome = (char*) malloc(sizeof(char)*110);
    return nome;
}

alunos* cria_e_preenche_um_aluno()
{
    alunos* novo = (alunos*) malloc(sizeof(alunos));
    novo->nome = inicializa_nomes();

    printf("Digite o nome do aluno: ");
    getchar();
    fgets(novo->nome, sizeof(char)*110, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = 0;
    printf("%s\n", novo->nome);

    printf("Digite a matricula do aluno: ");
    scanf(" %d", &novo->matricula);
    printf("%d\n", novo->matricula);

    printf("Digite o número de telefone do aluno: ");
    novo->telefone = inicializa_nomes();
    fgets(novo->telefone, sizeof(char)*110, stdin);
    novo->telefone[strcspn(novo->telefone, "\n")] = 0;
    printf("%s\n", novo->telefone);

    return novo;
}

professores* cria_e_preenche_um_professor(){
    professores* novo = (professores*) malloc(sizeof(professores));
    novo->nome = inicializa_nomes();

    printf("Digite o nome do professor: ");
    fgets(novo->nome, sizeof(char)*110, stdin);
    novo->nome[strcspn(novo->nome, "\n")] = 0;

    printf("Digite o código do professor: ");
    scanf("%d", &novo->codigo);

    novo->departamento = inicializa_nomes();
    printf("Digite o departamento de lotação do professor: ");
    getchar();
    fgets(novo->departamento, sizeof(char)*110, stdin);
    printf("%s\n", novo->departamento);

    return novo;
}

projetos* cria_e_preenche_um_projeto(lista* lista_de_professores)
{
    projetos* novo = (projetos*)malloc(sizeof(projetos));
    professores* aux = NULL;
    int tipo_do_projeto = -1;
    int codigo_do_professor = -1;

    printf("Digite o código do projeto: ");
    scanf(" %d", &novo->codigo);

    novo->descricao = (char*) malloc(sizeof(char)*400);

    printf("Digite a descrição do projeto: ");
    getchar();
    fgets(novo->descricao, sizeof(char)*400, stdin);
    printf("%s\n", novo->descricao);

    while (tipo_do_projeto < 1 || tipo_do_projeto > 3)
    {
        printf("Para o tipo de projeto:\n - Digite 1 se \"ensino\"\n - Digite 2 se \"pesquisa\"\n - Digite 3 se \"extensão\".\n");
        printf("Resposta: ");
        scanf("%d", &tipo_do_projeto);
    } 
    novo->tipo = tipo_do_projeto;

    printf("Digite o orçamento aprovado para o projeto: ");
    scanf(" %f", &novo->orcamento_aprovado);

    novo->orcamento_disponivel = novo->orcamento_aprovado;

    while(aux == NULL)
    {
        printf("Digite o código do professor coordenador: ");
        scanf("%d", &codigo_do_professor);
        aux = acha_na_lista(lista_de_professores, codigo_do_professor, PROFESSORES, false);
        if(aux == NULL) printf("Professor não encontrado!\n");
        else 
        {
            printf("Professor %s encontrado!\n", aux->nome);
            novo->prof_coordenador = aux;
        }
    }
    
    return novo;
}

void* insere_no_fim_da_lista(void* ponteiro_dos_dados, lista* minha_lista){
    lista* ultimo_no = acha_ultimo_da_lista(minha_lista);
    lista* novo_no = (lista*) malloc(sizeof(lista));
    novo_no->dados = ponteiro_dos_dados;
    novo_no->next = NULL;

    if(minha_lista == NULL) return novo_no;
    ultimo_no->next = novo_no;

    return minha_lista;
}

// a lista que eu passo como "minha_lista" deve ser diferente para cada tipo de dado
// ou seja, eu crio uma lista void para cada uma das minhas structs
void* insere_no_inicio_da_lista(void* ponteiro_dos_dados, lista* minha_lista){ 
    lista* novo = (lista*) malloc(sizeof(lista));
    novo->dados = ponteiro_dos_dados;
    novo->next = minha_lista;
    return novo;
}

void* acha_na_lista(lista* minha_lista, int n, int tipo, bool isMatricula)
{
    //isMatricula == true se for matricula, false se for código
    lista* no_atual = minha_lista;
    int codigo_ou_matricula = -1;

    for(; no_atual != NULL; no_atual = no_atual->next)
    {
        if(tipo == PROJETOS) codigo_ou_matricula = ((projetos*)no_atual->dados)->codigo;
        else if(tipo == ALUNOS) codigo_ou_matricula = ((alunos*)no_atual->dados)->matricula;
        else if(tipo == PROFESSORES) codigo_ou_matricula = ((professores*)no_atual->dados)->codigo;
        else if(tipo == VINCULOS && isMatricula) codigo_ou_matricula = ((vinculos*)no_atual->dados)->aluno->matricula;
        else if(tipo == VINCULOS && !isMatricula) codigo_ou_matricula = ((vinculos*)no_atual->dados)->projeto->codigo;
        if(codigo_ou_matricula == n) return no_atual->dados;
    } 

    return NULL;
}

vinculos* cria_e_preenche_um_vinculo(lista* lista_alunos, lista* lista_projetos, lista* lista_vinculos){
    float valor_bolsa;
    int codigo_do_projeto, matricula;

    printf("Digite o código do projeto ao qual deseja vincular o aluno: ");
    scanf("%d", &codigo_do_projeto);
    printf("Digite o valor mensal da bolsa do aluno: ");
    scanf("%f", &valor_bolsa);

    projetos* temp = (projetos*) acha_na_lista(lista_projetos, codigo_do_projeto, PROJETOS, false);
    if (temp == NULL) {
        printf("Projeto não encontrado!\n");
        return NULL;
    }

    if(temp->orcamento_disponivel - (12*valor_bolsa) >= 0){
        vinculos* novo = (vinculos*) malloc(sizeof(vinculos));
        while(true)
        {
            printf("Digite a matrícula do aluno a ser vinculado: ");
            scanf("%d", &matricula);
            vinculos* ja_vinculado = (vinculos*) acha_na_lista(lista_vinculos, matricula, VINCULOS, true);
            if(ja_vinculado == NULL) break;
            printf("Aluno já vinculado a um projeto. Tente outro!\n");
        }
        
        alunos* aux = (alunos*) acha_na_lista(lista_alunos, matricula, ALUNOS, true);

        if(aux != NULL){
            novo->aluno = aux;
            novo->projeto = temp;
            novo->bolsa = valor_bolsa;
            temp->orcamento_disponivel -= 12*novo->bolsa;
            printf("Vínculo criado com sucesso!\n");
            return novo;
        }else{
            printf("Aluno inexistente! Não foi possível criar o vínculo.\n");
            free(novo);
            return NULL;
        }
    }else printf("Não foi possível vincular o aluno ao projeto, orçamento insuficiente para a bolsa!\n");

    return NULL;
}

void* acha_ultimo_da_lista(lista* minha_lista){
    if(minha_lista == NULL) return NULL;

    lista* no_atual = minha_lista;
    while(no_atual->next!=NULL) no_atual = no_atual->next;

    return no_atual;
}

void* busca_e_remove_vinculo(lista* minha_lista, alunos* aluno_buscado, projetos* projeto_buscado){
    
    lista* no_anterior  = NULL;
    alunos* aluno_encontrado;
    projetos* projeto_encontrado;

    for(lista* no_atual = minha_lista; no_atual != NULL; no_atual = no_atual->next){
        aluno_encontrado = ((vinculos*)no_atual->dados)->aluno;
        projeto_encontrado = ((vinculos*)no_atual->dados)->projeto;

        if(aluno_encontrado == aluno_buscado &&  projeto_encontrado == projeto_buscado){
            if(no_anterior == NULL)
            {
                no_anterior = no_atual;
                no_atual = no_atual->next;
                free(no_anterior);  
                return no_atual;
            }
            else if(no_atual->next == NULL){
                free(no_atual);
                no_anterior->next = NULL;
                return minha_lista;
            } 

            no_anterior->next = no_atual->next;
            free(no_atual);
            return minha_lista;
        }
        no_anterior = no_atual;
    }
    return NULL;
}

lista* exclui_vinculo(lista* lista_vinculos, lista* lista_alunos, lista* lista_projetos){
    int matricula, codigo_do_projeto, meses, valor_da_bolsa;
    printf("Digite o código do projeto do qual deseja remover o aluno: ");
    scanf("%d", &codigo_do_projeto);
    printf("Digite a matrícula do aluno que deseja remover do projeto: ");
    scanf("%d", &matricula);
    printf("Digite quantos meses de bolsa não serão mais pagos: ");
    scanf("%d", &meses);

    alunos* aluno_a_remover = (alunos*)acha_na_lista(lista_alunos, matricula, ALUNOS, true);
    projetos* projeto_em_questao = (projetos*) acha_na_lista(lista_projetos, codigo_do_projeto, PROJETOS, false);
    vinculos* vinculo = (vinculos*) busca_e_remove_vinculo(lista_vinculos, aluno_a_remover, projeto_em_questao);
    
    if(vinculo == NULL) printf("Nada a remover!\n");

    valor_da_bolsa = vinculo->bolsa;
    projeto_em_questao->orcamento_disponivel += meses*valor_da_bolsa;

    return lista_vinculos;
}

void imprime_lista(lista* minha_lista, int tipo_da_lista)
{
    char tipo_de_projeto[15];

    if(minha_lista == NULL)
    {
        printf("\nLista vazia!\n\n");
        return;
    }

    for(lista* no_atual = minha_lista; no_atual != NULL; no_atual = no_atual->next)
    {
        switch(tipo_da_lista)
        {
            case PROJETOS:
                if(((projetos*) no_atual->dados)->tipo == 0) sprintf(tipo_de_projeto, "Ensino");
                else if(((projetos*) no_atual->dados)->tipo == 1) sprintf(tipo_de_projeto, "Pesquisa");
                else if(((projetos*) no_atual->dados)->tipo == 2) sprintf(tipo_de_projeto, "Extensão");
                printf("\nCódigo do projeto: %d\n", ((projetos*) no_atual->dados)->codigo);
                printf("Tipo: %s\n", tipo_de_projeto);
                printf("Professor coordenador: %s\n", ((projetos*) no_atual->dados)->prof_coordenador->nome);
                printf("Descrição: %s\n", ((projetos*) no_atual->dados)->descricao);
                printf("Orçamento aprovado: %.2f\n", ((projetos*) no_atual->dados)->orcamento_aprovado);
                printf("Orçamento disponível: %.2f\n\n", ((projetos*) no_atual->dados)->orcamento_disponivel);
                break;
            case ALUNOS:
                printf("\nNome do aluno: %s\n", ((alunos*) no_atual->dados)->nome);
                printf("Matrícula: %d\n", ((alunos*) no_atual->dados)->matricula);
                printf("Telefone: %s\n\n", ((alunos*) no_atual->dados)->telefone);
                break;
            case PROFESSORES:
                printf("\nNome do professor: %s\n", ((professores*) no_atual->dados)->nome);
                printf("Código: %d\n", ((professores*) no_atual->dados)->codigo);
                printf("Departamento: %s\n\n", ((professores*) no_atual->dados)->departamento);
                break;
            case VINCULOS:
                printf("\nCódigo do Projeto: %d\n", ((vinculos*) no_atual->dados)->projeto->codigo);
                printf("Professor coordenador: %s\n", ((vinculos*) no_atual->dados)->projeto->prof_coordenador->nome);
                printf("Código do professor: %d\n", ((vinculos*) no_atual->dados)->projeto->prof_coordenador->codigo);
                printf("Aluno vinculado: %s\n", ((vinculos*) no_atual->dados)->aluno->nome);
                printf("Matrícula do aluno: %d\n\n", ((vinculos*) no_atual->dados)->aluno->matricula);
                printf("Bolsa: %.2f\n\n", ((vinculos*) no_atual->dados)->bolsa);
                break;
        }
    }
}

void imprime_relatorio_projeto(projetos* projeto, vinculos* vinculo)
{
    printf("\n\n\t\tRELATÓRIO DE PROJETO\n\n");
    printf("\tCódigo do projeto: %d", projeto->codigo);
    printf("\tTipo: ");
    
    if(projeto->tipo == 1) printf("Ensino\n");
    else if(projeto->tipo == 2) printf("Pesquisa\n");
    else if(projeto->tipo == 3) printf("Extensão\n");

    printf("\tProfessor coordenador: %s\n", projeto->prof_coordenador->nome);
    printf("Orçamento disponível: %lf\n", projeto->orcamento_disponivel);
    
    if(vinculo != NULL) printf("Aluno vinculado: %s", vinculo->aluno->nome);
    else printf("Não há alunos vinculados a este projeto.\n");
}

void desaloca_lista_de_alunos(lista* lista_alunos)
{
    lista* no_anterior = NULL;
    for(lista* no_atual = lista_alunos; no_atual != NULL; no_atual = no_atual->next)
    {
        if(no_anterior != NULL) free(no_anterior);
        free(((alunos*)no_atual->dados)->nome);
        free(((alunos*)no_atual->dados)->telefone);
        free(no_atual->dados);
        no_anterior = no_atual;
    }

    if(no_anterior != NULL) free(no_anterior);
}

void desaloca_lista_professores(lista* lista_professores)
{
    lista* no_anterior = NULL;
    for(lista* no_atual = lista_professores; no_atual != NULL; no_atual = no_atual->next)
    {
        if(no_anterior != NULL) free(no_anterior);
        free(((professores*)no_atual->dados)->nome);
        free(((professores*)no_atual->dados)->departamento);
        free(no_atual->dados);
        no_anterior = no_atual;
    }

    if(no_anterior != NULL) free(no_anterior);
}

void desaloca_lista_projetos(lista* lista_projetos)
{
    lista* no_anterior = NULL;
    for(lista* no_atual = lista_projetos; no_atual != NULL; no_atual = no_atual->next)
    {
        if(no_anterior != NULL) free(no_anterior);
        free(((projetos*)no_atual->dados)->descricao);
        free(no_atual->dados);
        no_anterior = no_atual;
    }

    if(no_anterior != NULL) free(no_anterior);
}

void desaloca_lista_vinculos(lista* lista_vinculos)
{
    lista* no_anterior = NULL;
    for(lista* no_atual = lista_vinculos; no_atual != NULL; no_atual = no_atual->next)
    {
        if(no_anterior != NULL) free(no_anterior);
        free(no_atual->dados);
        no_anterior = no_atual;
    }

    if(no_anterior != NULL) free(no_anterior);
}
