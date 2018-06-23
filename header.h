#define HEADER_H_INCLUDED
#include <locale.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX_STRING 500

typedef struct data{
    int dia;
    int mes;
    int ano;
}Data;

typedef struct hora{
    int hora;
    int minutos;
}Hora;

typedef struct duracao{
    int horas;
    int minutos;
}Duracao;

typedef struct sala{
    int vagas;
    char* nome;
}Sala;

typedef struct exame{
    char* disciplina;
    char *epoca;
    Data *data;
    Hora *hora;
    Duracao *duracao;
    Sala *sala;
}Exame;

typedef struct lnode_alunos * Lista_Alunos;
typedef struct lnode_disciplinas * Lista_Disciplinas;
typedef struct lnode_exames * Lista_Exames;
typedef struct lnode_salas * Lista_Salas;

typedef struct aluno{
    char *nome;
    int numero_de_estudante;
    char *curso;
    int ano_de_matricula;
    char *regime;
}Aluno;

typedef struct disciplina{
    char *nome;
    char *docente_responsavel;
}Disciplina;

typedef struct lnode_alunos{
    Aluno *aluno;
    Lista_Exames exames;
    Lista_Alunos next;
}Lista_alunos_node;

typedef struct lnode_disciplinas{
    Disciplina *disciplina;
    Lista_Exames exames;
    Lista_Disciplinas next;
}Lista_disciplinas_node;

typedef struct lnode_salas{
    Sala* sala;
    Lista_Salas next;
}Lista_Salas_node;

typedef struct lnode_exames{
    Exame *exame;
    Lista_Salas salas;
    Lista_Alunos alunos;
    Lista_Exames next;
}Lista_exames_node;

/* func.c */
int compara_nomes(char*nome1,char*nome2);
int compara_datas(Data *d1, Data *d2, Hora* h1, Hora* h2);
void procura_lista_alunos(Lista_Alunos lista, Aluno* chave, Lista_Alunos *ant, Lista_Alunos *atual);
void procura_lista_exame(Lista_Exames lista, Exame* chave, Lista_Exames *ant, Lista_Exames *atual);
void procura_lista_disciplinas(Lista_Disciplinas lista, Disciplina *chave, Lista_Disciplinas *ant, Lista_Disciplinas *atual);
void elimina_lista_alunos(Lista_Alunos lista_alunos,Aluno*aluno);
void elimina_lista_exames(Lista_Exames lista_exames,Exame *exame);
void elimina_lista_disciplinas(Lista_Disciplinas lista_disciplinas,Disciplina *disciplina);
Lista_Alunos cria_lista_alunos();
Lista_Disciplinas cria_lista_disciplinas();
Lista_Exames cria_lista_exames();
void imprime_exames(Lista_Exames lista_exames,Exame * exame);
void imprime_alunos(Aluno* aluno);
void imprime_disciplinas(Disciplina*disciplina);
void associar_exames_alunos(Lista_Alunos lista_principal_alunos, Lista_Disciplinas lista_principal_disciplinas, Lista_Exames lista_principal_exames,Exame * aux_e,Aluno * aux_a, Disciplina * aux_d);
int verifica_data(Data * data);
int verifica_hora(Hora * hora);
void retira_enter(char* str);
int devolve_inteiro();
int devolve_nestudante();
char* devolve_nome();
Exame* escolhe_exame(Lista_Exames lista_exames);
Aluno* escolhe_aluno(Lista_Alunos lista_alunos);
Disciplina* escolhe_disciplina(Lista_Disciplinas lista_disciplinas);
void insere_lista_principal_alunos(Lista_Alunos lista_principal_alunos, Aluno* aluno);
void insere_lista_principal_disciplinas(Lista_Disciplinas lista_principal_disciplinas, Disciplina* disciplina);
void insere_lista_principal_exames(Lista_Exames lista_principal_exames, Exame* exame);
void criar_aluno(Lista_Alunos lista_principal_alunos,char*nome,char*curso,char*regime,int ano_de_matricula, int numero_de_estudante);
void criar_aluno_manual(Lista_Alunos lista_principal_alunos);
void apagar_aluno(Lista_Alunos lista_alunos);
void alterar_aluno(Lista_Alunos lista_alunos);
void imprime_exames_aluno(Lista_Alunos lista_principal_alunos,Lista_Exames lista_principal_exames);
void criar_disciplina(Lista_Disciplinas lista_principal_disciplinas,char*nome,char*docente_responsavel);
void criar_disciplina_manual(Lista_Disciplinas lista_principal_disciplinas);
void altera_disciplina(Lista_Disciplinas lista_disciplinas);
void apagar_disciplina(Lista_Disciplinas lista_disciplinas);
void criar_exame(Lista_Exames lista_principal_exames,Data* data, Hora* hora, Duracao* duracao, char*epoca,char*disciplina,Sala*sala);
void criar_exame_manual(Lista_Exames lista_principal_exames);
void altera_exame(Lista_Exames lista_exames);
void apagar_exame(Lista_Exames lista_exames);
void insere_aluno_exame(Lista_Exames lista_principal_exames,Lista_Disciplinas lista_principal_disciplinas,Lista_Alunos lista_principal_alunos);
void imprime_lista_exames(Lista_Exames lista_principal_exames);
void imprime_alunos_exame();
int verifica_salas(Lista_Exames lista_principal_exames,char*nome,Data*data,Hora*hora,Duracao*duracao);
void menu_alunos(Lista_Alunos lista_principal_alunos,Lista_Exames lista_principal_exames);
void menu_disciplinas(Lista_Disciplinas lista_principal_disciplinas);
void menu_exames(Lista_Exames lista_principal_exames,Lista_Disciplinas lista_principal_disciplinas, Lista_Alunos lista_principal_alunos);

/* ficheiro.c */
void verifica_ficheiros();
void guarda_listas(Lista_Alunos lista_principal_alunos, Lista_Disciplinas lista_principal_disciplinas, Lista_Exames lista_principal_exames);
void carrega_listas(Lista_Alunos lista_principal_alunos,Lista_Disciplinas lista_principal_disciplinas, Lista_Exames lista_principal_exames);
