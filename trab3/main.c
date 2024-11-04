#include "bolsistas.h"
#include "menu.h"

int main() {
    lista* lista_alunos = cria_nova_lista();
    lista* lista_professores = cria_nova_lista();
    lista* lista_projetos = cria_nova_lista();
    lista* lista_vinculos = cria_nova_lista();

    int sair;
    while(true) 
    {
        exibe_menu();
        sair = processa_escolha(&lista_alunos, &lista_professores, &lista_projetos, &lista_vinculos);
        if(sair == -1) break;
    }

    desaloca_lista_de_alunos(lista_alunos);
    desaloca_lista_professores(lista_professores);  
    desaloca_lista_projetos(lista_projetos);
    desaloca_lista_vinculos(lista_vinculos);
}
