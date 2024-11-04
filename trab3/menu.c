#include "bolsistas.h"

void exibe_menu() {
    printf("\n\n\t\tMENU\n\n");
    printf("1. Criar novo aluno\n");
    printf("2. Criar novo professor\n");
    printf("3. Criar novo projeto\n");
    printf("4. Criar novo vínculo\n");
    printf("5. Listar alunos\n");
    printf("6. Listar professores\n");
    printf("7. Listar projetos\n");
    printf("8. Listar vínculos\n");
    printf("9. Imprimir relatório de projeto\n");
    printf("0. Sair\n");
    printf("Escolha uma opção: ");
}

int processa_escolha(lista** lista_alunos, lista** lista_professores, lista** lista_projetos, lista** lista_vinculos)
{
    alunos* aluno_novo;
    professores* professor_novo;
    projetos* projeto_novo;
    vinculos* vinculo_novo;

    int escolha = 0;
    scanf("%d", &escolha);
    switch (escolha) {
        case 0:
            return -1;
        case 1:
            aluno_novo = cria_e_preenche_um_aluno();
            *lista_alunos = (lista*) insere_no_inicio_da_lista(aluno_novo, *lista_alunos);
            break;
        case 2:
            professor_novo = cria_e_preenche_um_professor();
            *lista_professores = (lista*) insere_no_inicio_da_lista(professor_novo, *lista_professores);
            break;
        case 3:
            projeto_novo = cria_e_preenche_um_projeto(*lista_professores);
            *lista_projetos = (lista*) insere_no_inicio_da_lista(projeto_novo, *lista_projetos);
            break;
        case 4:
            vinculo_novo = cria_e_preenche_um_vinculo(*lista_alunos, *lista_projetos, *lista_vinculos);
            *lista_vinculos = (lista*) insere_no_inicio_da_lista(vinculo_novo, *lista_vinculos);
            break;
        case 5:
            imprime_lista(*lista_alunos, ALUNOS);
            break;
        case 6:
            imprime_lista(*lista_professores, PROFESSORES);
            break;
        case 7:
            imprime_lista(*lista_projetos, PROJETOS);
            break;
        case 8:
            imprime_lista(*lista_vinculos, VINCULOS);
            break;
        case 9: {
            int codigo_do_projeto;
            projetos* projeto = NULL;
            do
            {
                printf("Digite o código do projeto: ");
                scanf("%d", &codigo_do_projeto);
                projeto = acha_na_lista(*lista_projetos, codigo_do_projeto, PROJETOS, false);
                if(projeto == NULL) printf("Projeto não encontrado!\n");
            } while (projeto == NULL);
            vinculos* vinculo = acha_na_lista(*lista_vinculos, codigo_do_projeto, VINCULOS, false);
            imprime_relatorio_projeto(projeto, vinculo);
            break;
        }
        default:
            printf("Opção inválida! Tente novamente.\n");
    }

    return 0;
}
