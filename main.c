#include "header.h"

void menu(Lista_Alunos lista_principal_alunos,Lista_Disciplinas lista_principal_disciplinas,Lista_Exames lista_principal_exames){
        int opcao;
        while(1){
        printf("MENU:\n");
        printf("[1] Alunos\n");
        printf("[2] Disciplinas\n");
        printf("[3] Exames\n");
        printf("[4] Sair do programa.\n");
        opcao = devolve_inteiro();
        system("cls");

        switch(opcao){
            case 1:
                menu_alunos(lista_principal_alunos,lista_principal_exames);
                break;
            case 2:
                menu_disciplinas(lista_principal_disciplinas);
                break;
            case 3:
                menu_exames(lista_principal_exames,lista_principal_disciplinas,lista_principal_alunos);
                break;
            case 4:
                printf("Programa terminado com sucesso.");
                return;
            default:
                printf("Opção inválida!\n");
                break;
    system("cls");
    }
    printf("Prima Enter para voltar ao menu.");
    while(getchar()!='\n');
    system("cls");
    }
}
int main()
{
    Lista_Alunos lista_principal_alunos;
    Lista_Disciplinas lista_principal_disciplinas;
    Lista_Exames lista_principal_exames;

    lista_principal_alunos = cria_lista_alunos();
    lista_principal_disciplinas = cria_lista_disciplinas();
    lista_principal_exames = cria_lista_exames();

    verifica_ficheiros();
    carrega_listas(lista_principal_alunos,lista_principal_disciplinas,lista_principal_exames);

    setlocale(LC_ALL, "Portuguese");
    menu(lista_principal_alunos,lista_principal_disciplinas,lista_principal_exames);

    guarda_listas(lista_principal_alunos,lista_principal_disciplinas,lista_principal_exames);
    return 0;
}
