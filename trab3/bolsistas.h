#ifndef BOLSISTAS_H
#define BOLSISTAS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define PROJETOS 0
#define ALUNOS 1
#define PROFESSORES 2
#define VINCULOS 3

typedef struct Lista{
    void* dados;
    struct Lista* next;
}lista;

typedef struct Alunos{
    int matricula;
    char* nome;
    char* telefone;
}alunos;

typedef struct Professores{
    int codigo;
    char* nome;
    char* departamento;
}professores;

typedef struct Projetos{
    int codigo;
    char* descricao;
    int tipo;
    float orcamento_aprovado;
    float orcamento_disponivel;
    professores* prof_coordenador;
}projetos;

typedef struct Vinculos{
    alunos* aluno;
    projetos* projeto;
    float bolsa;
}vinculos;

void* cria_nova_lista();
char* inicializa_nomes();
void* acha_ultimo_da_lista(lista* minha_lista);
void* acha_na_lista(lista* minha_lista, int n, int tipo,bool isMatricula);
void* busca_e_remove_vinculo(lista* minha_lista, alunos* aluno, projetos* projeto);
alunos* cria_e_preenche_um_aluno();
professores* cria_e_preenche_um_professor();
projetos* cria_e_preenche_um_projeto(lista* minha_lista);
void* insere_no_fim_da_lista(void* ponteiro_dos_dados, lista* minha_lista);
void* insere_no_inicio_da_lista(void* ponteiro_dos_dados, lista* minha_lista);
lista* exclui_vinculo(lista* lista_vinculos, lista* lista_alunos, lista* lista_projetos);
vinculos* cria_e_preenche_um_vinculo(lista* lista_alunos, lista* lista_projetos, lista* lista_vinculos);
void imprime_relatorio_projeto(projetos* projeto, vinculos* vinculo);
void desaloca_lista_de_alunos(lista* lista_alunos);
void desaloca_lista_professores(lista* lista_professores);
void desaloca_lista_projetos(lista* lista_projetos);
void desaloca_lista_vinculos(lista* lista_vinculos);

#endif
