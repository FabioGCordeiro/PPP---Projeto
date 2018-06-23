#include "header.h"

int compara_nomes(char*nome1,char*nome2){
    int i;
    for(i=0;nome1[i]!='\0' || nome2[i]!='\0';i++){
        if(nome1[i]!=nome2[i]){
            if(nome1[i]<nome2[i])
                return -1;
            else
                return 1;
        }
    }
    return 0;
}

int compara_datas(Data *d1, Data *d2, Hora* h1, Hora* h2){
    int a, b;
    a=(d1->ano)*10000+(d1->mes)*100+(d1->dia);
    b=(d2->ano)*10000+(d2->mes)*100+(d2->dia);
    if (a>b) return 1;
    else if (a<b) return -1;
    else{
        a=h1->hora*100+h1->minutos;
        b=h2->hora*100+h2->minutos;
        if (a>b) return 1;
        else if (a<b)
            return -1;
        else
            return 0;
    }
}

int verifica_nestudante(Lista_Alunos lista_principal_alunos, int n_estudante){
    Lista_Alunos la_aux;
    int aux;
    la_aux=lista_principal_alunos;
    aux = la_aux->next->aluno->numero_de_estudante;
    if(la_aux->next==NULL)
        return 0;
    while(la_aux->next!=NULL){
        if(aux!=n_estudante){
                la_aux=la_aux->next;
        }
        else{
                la_aux=la_aux->next;
                break;
        }
    }
    if(aux==n_estudante)
        return 1;
    return 0;

}

int encontra_posicao_aluno(Lista_Alunos lista_principal_alunos, Aluno* aluno){
    Lista_Alunos la_aux;
    int i;
    la_aux=lista_principal_alunos;
    for(i=0;la_aux->aluno!=aluno;i++)
        la_aux=la_aux->next;
    return i;
}

int encontra_posicao_disciplina(Lista_Disciplinas lista_principal_disciplinas, Disciplina* disciplina){
    Lista_Disciplinas ld_aux;
    int i;
    ld_aux=lista_principal_disciplinas;
    for(i=0;ld_aux->disciplina!=disciplina;i++)
        ld_aux=ld_aux->next;
    return i;
}

int encontra_posicao_exame(Lista_Exames lista_principal_exames, Exame* exame){
    Lista_Exames le_aux;
    int i;
    le_aux=lista_principal_exames;
    for(i=0;le_aux->exame!=exame;i++)
        le_aux=le_aux->next;
    return i;
}

Aluno *aluno_por_posicao(Lista_Alunos lista_principal_alunos, int posicao){
    Lista_Alunos la_aux;
    int i;
    la_aux=lista_principal_alunos;
    for(i=0;i<posicao; i++)
        la_aux=la_aux->next;
    return la_aux->aluno;
}

Exame *exame_por_posicao(Lista_Exames lista_principal_exames, int posicao){
    Lista_Exames le_aux;
    int i;
    le_aux=lista_principal_exames;
    for(i=0;i<posicao; i++)
        le_aux=le_aux->next;
    return le_aux->exame;
}

void procura_lista_alunos(Lista_Alunos lista, Aluno* chave, Lista_Alunos *ant, Lista_Alunos *atual){
    *ant = lista;
    *atual = lista->next;
    while((*atual) != NULL && compara_nomes(((*atual)->aluno->nome),chave->nome)==-1)
    {
        *ant = *atual;
        * atual = (*atual)->next;
    }
    if((*atual) != NULL && compara_nomes(((*atual)->aluno->nome),chave->nome)!=0)
        *atual=NULL;
}

void procura_lista_exame(Lista_Exames lista, Exame* chave, Lista_Exames *ant, Lista_Exames *atual){
    *ant = lista;
    *atual = lista->next;
    while((*atual) != NULL && compara_datas(((*atual)->exame->data),chave->data,((*atual)->exame->hora),chave->hora)==-1)
    {
        *ant = *atual;
        * atual = (*atual)->next;
    }
    if((*atual) != NULL && compara_datas(((*atual)->exame->data),chave->data,((*atual)->exame->hora),chave->hora)!=0)
        *atual=NULL;
}


void procura_lista_disciplinas(Lista_Disciplinas lista, Disciplina *chave, Lista_Disciplinas *ant, Lista_Disciplinas *atual){
    *ant = lista;
    *atual = lista->next;
    while((*atual) != NULL && compara_nomes(((*atual)->disciplina->nome),chave->nome)==-1)
    {
        *ant = *atual;
        * atual = (*atual)->next;
    }
    if((*atual) != NULL && compara_nomes(((*atual)->disciplina->nome),chave->nome)!=0)
        *atual=NULL;
}

void procura_lista_salas(Lista_Salas lista, Sala *chave, Lista_Salas *ant, Lista_Salas *atual){
    *ant = lista;
    *atual = lista->next;
    while((*atual) != NULL && compara_nomes(((*atual)->sala->nome),chave->nome)==-1)
    {
        *ant = *atual;
        * atual = (*atual)->next;
    }
    if((*atual) != NULL && compara_nomes(((*atual)->sala->nome),chave->nome)!=0)
        *atual=NULL;
}

void elimina_lista_alunos(Lista_Alunos lista_alunos,Aluno*aluno){
    Lista_Alunos ant,atual;
    procura_lista_alunos(lista_alunos,aluno,&ant,&atual);
    if(atual != NULL){
        ant->next = atual->next;
        free(atual);
        printf("Aluno eliminado com sucesso!\n");
    }
}

void elimina_lista_exames(Lista_Exames lista_exames,Exame *exame){
    Lista_Exames ant,atual;
    procura_lista_exame(lista_exames,exame,&ant,&atual);
    if(atual != NULL){
        ant->next = atual->next;
        free(atual);
        printf("Exame apagado com sucesso!\n");
    }
}

void elimina_lista_disciplinas(Lista_Disciplinas lista_disciplinas,Disciplina *disciplina){
    Lista_Disciplinas ant,atual;
    procura_lista_disciplinas(lista_disciplinas,disciplina,&ant,&atual);
    if(atual != NULL){
        ant->next = atual->next;
        free(atual);
        printf("Disciplina eliminada com sucesso!\n");
    }
}

int procura_aluno_de_exame(Lista_Exames node_exames, Aluno* aux_a){
    Lista_Alunos percorre_aluno;
    percorre_aluno=node_exames->alunos;
    if(percorre_aluno->next==NULL)
        return 0;
    while(percorre_aluno->next!=NULL){
        if(percorre_aluno->next->aluno!=aux_a){
                percorre_aluno=percorre_aluno->next;
        }
        else{
                percorre_aluno=percorre_aluno->next;
                break;
        }
    }
    if(percorre_aluno->aluno==aux_a)
        return 1;
    return 0;
}

Lista_Salas cria_lista_salas(){
    Lista_Salas aux;

    aux=(Lista_Salas)malloc(sizeof(Lista_Salas_node));
    if(aux!=NULL){
        aux->sala=malloc(sizeof(Lista_Salas_node));
        aux->sala->vagas = 0;
        aux->sala->nome=NULL;
        aux->next=NULL;
    }
    else
        printf("Erro na alocação de memória. \n");
    return aux;
}

Lista_Alunos cria_lista_alunos(){
Lista_Alunos aux;

    aux = (Lista_Alunos) malloc (sizeof (Lista_alunos_node));
    if (aux != NULL){
        aux->aluno = NULL;
        aux->exames = malloc(sizeof(Lista_exames_node));
        aux->exames->alunos = NULL;
        aux->exames->exame = NULL;
        aux->exames->next = NULL;
        aux->next = NULL;
    }
    else
        printf("Erro na alocação de memória.\n");
    return aux;
}

Lista_Disciplinas cria_lista_disciplinas(){
    Lista_Disciplinas aux;

    aux = (Lista_Disciplinas) malloc (sizeof (Lista_disciplinas_node));

    if (aux != NULL){
        aux->disciplina = NULL;
        aux->exames = malloc(sizeof(Lista_exames_node));
        aux->exames->alunos = NULL;
        aux->exames->exame = NULL;
        aux->exames->next = NULL;
        aux->next = NULL;
    }
    else
        printf("Erro na alocação de memória.\n");
    return aux;
}

Lista_Exames cria_lista_exames(){
    Lista_Exames aux;

    aux = (Lista_Exames) malloc (sizeof (Lista_exames_node));

    if (aux != NULL){
        aux->exame = NULL;
        aux->alunos = malloc(sizeof(Lista_alunos_node));
        aux->salas = malloc(sizeof(Lista_Salas_node));
        aux->alunos->aluno = NULL;
        aux->alunos->exames = NULL;
        aux->alunos->next = NULL;
        aux->salas->sala = NULL;
        aux->salas->next = NULL;
        aux->next = NULL;
    }
    else
        printf("Erro na alocação de memória.\n");
    return aux;
}

void imprime_salas(Lista_Salas lista){
    while(lista->next!=NULL){
        printf("%s ",lista->next->sala->nome);
        lista=lista->next;
    }
    printf("\n");
}

void imprime_exames(Lista_Exames lista_exames, Exame * exame){
    printf("Disciplina: %s - Data: %02d/%02d/%04d - Hora: %02d:%02d - Duração: %02d:%02d - Vagas: %02d - Época: %s - Sala(s): ",exame->disciplina,exame->data->dia,exame->data->mes,exame->data->ano,exame->hora->hora,exame->hora->minutos,exame->duracao->horas,exame->duracao->minutos,exame->sala->vagas,exame->epoca);
    while(lista_exames->next!=NULL){
        if(lista_exames->exame!=exame)
            lista_exames=lista_exames->next;
        else{
            lista_exames=lista_exames->next;
            break;
        }
    }
    imprime_salas(lista_exames->salas);
}

void imprime_alunos(Aluno* aluno){
    printf("Nome: %s - Nº de estudante: %d - Ano de matrícula: %d - Curso: %s - Regime: %s\n",aluno->nome,aluno->numero_de_estudante,aluno->ano_de_matricula,aluno->curso,aluno->regime);
}

void imprime_disciplinas(Disciplina*disciplina){
    printf("Nome: %s - Docente Responsável: %s\n",disciplina->nome,disciplina->docente_responsavel);
}

int verifica_epoca(char*epoca){
    char*teste1 = "Normal";
    char*teste2 = "Recurso";
    char*teste3 = "Especial";

    if (strcmp(epoca,teste1)==0)
        return 1;
    else if (strcmp(epoca,teste2) ==0)
        return 1;
    else if (strcmp(epoca,teste3)==0)
        return 1;
    else
        return 0;
}

int verifica_data(Data * data){
    int dia,mes,ano;
    dia = data->dia;
    mes = data->mes;
    ano = data->ano;

    if((dia>=1) && (mes>=1 && mes<= 12) && ano>=0){
        if(mes==2){
            if (dia<=28)
                return 1;
            else if (((ano % 400 == 0) || ((ano % 4 == 0) && (ano % 100 != 0))) && dia==29)
                return 1;
        }
        else if ((mes == 4 || mes == 6 || mes == 9 || mes == 11) && (dia<=30))
            return 1;
        else if ((mes == 1 || mes == 3 || mes == 5 || mes == 7 || mes == 8 || mes == 8 || mes == 10 || mes == 12) && (dia<=31))
            return 1;
    }
    return 0;
}

int verifica_hora(Hora * hora){
    int horas,minutos;

    horas = hora->hora;
    minutos = hora->minutos;

    if ((horas < 0) || (horas>23) || (minutos<0) || (minutos>59))
        return 0;
    return 1;
}

void retira_enter(char* str){
    int len;
    len=strlen(str);
    if(len>0 && str[len-1] == '\n')
        str[len-1] = '\0';
}

int devolve_inteiro(){
    char numero[MAX_STRING];
    int i, aux;

    do{
        fgets(numero, MAX_STRING, stdin);
        retira_enter(numero);

        aux=0;
        for(i=0; numero[i] != '\0'; i++){
            if(isdigit(numero[i]))
                aux++;
        }
        if (aux != i || i==0)
            printf("Número introduzido inválido. Introduza de novo: ");
        else if (strlen(numero)>10)
            printf("Apenas permitidos números até 10 dígitos. Introduza de novo: ");
    }while(aux != i || i==0 || strlen(numero)>10);

    return atoi(numero);
}

int devolve_nestudante(){
    char numero[MAX_STRING];
    int i, aux;

    do{
        fgets(numero, MAX_STRING, stdin);
        retira_enter(numero);

        aux=0;
        for(i=0; numero[i] != '\0'; i++){
            if(isdigit(numero[i]))
                aux++;
        }
        if (aux != i || i==0)
            printf("Número introduzido inválido. Introduza de novo: ");
        else if (strlen(numero)!=10)
            printf("Apenas permitidos números com 10 dígitos. Introduza de novo: ");
    }while(aux != i || i==0 || strlen(numero)!=10);

    return atoi(numero);
}

char *devolve_nome(){
    char *nome;
    char recebido[MAX_STRING];
    int contador, i, invalido;

    do{
        i=0;
        contador=0;
        invalido=0;
        fgets(recebido, MAX_STRING, stdin);
        retira_enter(recebido);
        while(recebido[i] != '\0'){
            if((recebido[i]>='A' && recebido[i]<='Z') || (recebido[i]>='a' && recebido[i]<='z') || recebido[i] == ' ' || recebido[i] == '-')
                contador++;
            i++;
        }
        if(recebido[0] == ' ' || recebido[0] == '\0' || recebido[strlen(recebido)-1] == ' ' || contador != i){
            printf("Nome inválido. Insira de novo: ");
            invalido=1;
        }
    }while(invalido==1);
    nome = strdup(recebido);
    return nome;
}

Exame* escolhe_exame(Lista_Exames lista_exames){
    Lista_Exames aux;
    int i,invalido,opcao;

    aux=lista_exames;
    system("cls");

    i=0;
    if(aux->next==NULL){
        printf("Sem exames disponíveis!\n");
        return NULL;
    }
    else{
        printf("Escolha o exame:\n");
        while(aux->next!=NULL){
            i++;
            printf("[%d] ",i);
            aux=aux->next;
            imprime_exames(lista_exames,aux->exame);
        }
    }
    printf("Escolha a opção:\n");
    do{
        invalido=0;
        opcao=devolve_inteiro();
        if(opcao<1 || opcao>i){
            invalido=1;
            printf("Opção inexistente. Escolha outra vez: ");
        }
    }while(invalido==1);

    aux=lista_exames->next;
    for(i=1;i<opcao;i++){
        aux=aux->next;
    }
    return aux->exame;
}

Aluno* escolhe_aluno(Lista_Alunos lista_alunos){
    Lista_Alunos aux;
    int i,invalido,opcao;

    aux=lista_alunos;
    system("cls");

    i=0;
    if(aux->next==NULL){
        printf("Sem alunos disponíveis!\n");
        return NULL;
    }
    else{
        printf("Escolha o aluno:\n");
        while(aux->next!=NULL){
            i++;
            printf("[%d] ",i);
            aux=aux->next;
            imprime_alunos(aux->aluno);
        }
    }
        printf("Escolha a opção:\n");
    do{
        invalido=0;
        opcao=devolve_inteiro();
        if(opcao<1 || opcao>i){
            invalido=1;
            printf("Opção inexistente. Escolha outra vez: ");
        }
    }while(invalido==1);

    aux=lista_alunos->next;
    for(i=1;i<opcao;i++){
        aux=aux->next;
    }
    return aux->aluno;
}

Disciplina* escolhe_disciplina(Lista_Disciplinas lista_disciplinas){
    Lista_Disciplinas aux;
    int i,invalido,opcao;

    aux=lista_disciplinas;
    system("cls");

    i=0;
    if(aux->next==NULL){
        printf("Sem disciplinas disponíveis!\n");
        return NULL;
    }
    else{
        printf("Escolha a disciplina:\n");
        while(aux->next!=NULL){
            i++;
            printf("[%d] ",i);
            aux=aux->next;
            imprime_disciplinas(aux->disciplina);
        }
    }
        printf("Escolha a opção:\n");
    do{
        invalido=0;
        opcao=devolve_inteiro();
        if(opcao<1 || opcao>i){
            invalido=1;
            printf("Opção inexistente. Escolha outra vez: ");
        }
    }while(invalido==1);

    aux=lista_disciplinas->next;
    for(i=1;i<opcao;i++){
        aux=aux->next;
    }
    return aux->disciplina;
}
void insere_lista_principal_alunos(Lista_Alunos lista_principal_alunos, Aluno* aluno){
    Lista_Alunos novo;
    Lista_Alunos ant, inutil;


    novo = cria_lista_alunos();

    if(novo!=NULL){
        novo->aluno=aluno;
        procura_lista_alunos(lista_principal_alunos,aluno,&ant,&inutil);
        novo->next=ant->next;
        ant->next=novo;
    }
}

void insere_lista_principal_disciplinas(Lista_Disciplinas lista_principal_disciplinas, Disciplina* disciplina){
    Lista_Disciplinas novo,ant,inutil;

    novo = cria_lista_disciplinas();


    if(novo!=NULL){
        novo->disciplina=disciplina;
        procura_lista_disciplinas(lista_principal_disciplinas,disciplina,&ant,&inutil);
        novo->next=ant->next;
        ant->next=novo;
    }
}

void insere_lista_principal_exames(Lista_Exames lista_principal_exames, Exame* exame){
    Lista_Exames novo,ant,inutil;

    novo = cria_lista_exames();


    if(novo!=NULL){
        novo->exame=exame;
        procura_lista_exame(lista_principal_exames,exame,&ant,&inutil);
        novo->next=ant->next;
        ant->next=novo;
    }
}

void insere_lista_salas(Lista_Salas lista_salas, Sala* sala){
    Lista_Salas novo,ant,inutil;

    novo = cria_lista_salas();


    if(novo!=NULL){
        novo->sala=sala;
        procura_lista_salas(lista_salas,sala,&ant,&inutil);
        novo->next=ant->next;
        ant->next=novo;
    }
}

void criar_aluno(Lista_Alunos lista_principal_alunos,char*nome,char*curso,char*regime,int ano_de_matricula, int numero_de_estudante){
    Aluno * aluno = (Aluno*)malloc(sizeof(Aluno));
    if(aluno==NULL){
        printf("Erro na alocação de memória.\n");
        return;
    }
    aluno->curso = malloc(sizeof(char)*MAX_STRING);
    aluno->nome = malloc(sizeof(char)*MAX_STRING);
    aluno->regime = malloc(sizeof(char)*MAX_STRING);
    aluno->ano_de_matricula=ano_de_matricula;
    strcpy(aluno->curso,curso);
    strcpy(aluno->nome,nome);
    aluno->numero_de_estudante=numero_de_estudante;
    strcpy(aluno->regime,regime);

    insere_lista_principal_alunos(lista_principal_alunos,aluno);
    free(curso);
    free(nome);
    free(regime);
}
void criar_aluno_manual(Lista_Alunos lista_principal_alunos){
    char * nome;
    char * curso;
    char * regime;
    int ano_de_matricula = 0;
    int numero_de_estudante = 0;
    int invalido;
    printf("Nome: ");
    nome=devolve_nome();
    printf("Numero de estudante: ");
    do{
    numero_de_estudante=devolve_nestudante();
    invalido = verifica_nestudante(lista_principal_alunos,numero_de_estudante);
    if(invalido==1)
        printf("Número de estudante já introduzido para outro aluno! Introduza um número de estudante válido: ");
    }while(invalido==1);
    printf("Curso: ");
    curso=devolve_nome();
    printf("Ano de Matricula: ");
    ano_de_matricula=devolve_inteiro();
    printf("Regime: ");
    regime=devolve_nome();

    criar_aluno(lista_principal_alunos,nome,curso,regime,ano_de_matricula,numero_de_estudante);
}

void apagar_aluno(Lista_Alunos lista_alunos){
    Aluno * aux_a;
    Exame * aux_e;
    Lista_Exames le_sec;
    Lista_Alunos la_aux;

    aux_a=escolhe_aluno(lista_alunos);
    if(aux_a==NULL)
        return;

    la_aux=lista_alunos->next;
    while(la_aux->aluno!=aux_a)
        la_aux=la_aux->next;

    le_sec=la_aux->exames;
        while(le_sec->next != NULL)
            le_sec=le_sec->next;
        le_sec->next=NULL;

    elimina_lista_alunos(lista_alunos,aux_a);
}

void alterar_aluno(Lista_Alunos lista_alunos){
    Aluno* aux;
    int opcao;
    int temp;
    int invalido = 0;
    printf("Escolha o aluno:\n");
    aux = escolhe_aluno(lista_alunos);
    if(aux==NULL)
        return;
    printf("Qual a informação que pretende alterar?\n");
    printf("[1] Nome\n[2] Número de estudante\n[3] Curso\n[4] Ano de matrícula\n[5] Regime\n");
    opcao = devolve_inteiro();

    switch(opcao){
        case 1:
            printf("Introduza o novo nome: ");
            aux->nome=devolve_nome();
            break;
        case 2:
            printf("Introduza o novo numero de estudante: ");
            do{
            temp=devolve_inteiro();
            invalido = verifica_nestudante(lista_alunos,temp);
            if(invalido == 1)
                printf("Número de estudante associado a outro aluno! Introduza um número de estudante válido: ");
            else
                aux->numero_de_estudante=opcao;
            }while(invalido==1);
            break;
        case 3:
            printf("Introduza o novo curso: ");
            aux->curso=devolve_nome();
            break;
        case 4:
            printf("Introduza o novo ano de matrícula: ");
            aux->ano_de_matricula=devolve_inteiro();
            break;
        case 5:
            printf("Introduza o novo regime: ");
                aux->regime=devolve_nome();
                break;
        default:
            printf("Opção inválida. Introduza de novo: ");
    }
    printf("Aluno alterado com sucesso!\n");
}

void imprime_exames_disciplina(Lista_Disciplinas lista_principal_disciplinas){
    Disciplina* disciplina;
    Lista_Exames le_sec;
    Lista_Disciplinas ld_aux;

    ld_aux = lista_principal_disciplinas;
    disciplina = escolhe_disciplina(ld_aux);
    if(disciplina==NULL)
        return;
    while(disciplina != ld_aux->disciplina)
        ld_aux=ld_aux->next;
    system("cls");

    le_sec=ld_aux->exames;
    if(le_sec->next==NULL){
        printf("A disciplina não tem nenhum exame.\n");
        return;
    }
    printf("Lista de exames desta disciplina:\n");
    while(le_sec->next!=NULL){
        le_sec=le_sec->next;
        imprime_exames(le_sec,le_sec->exame);
    }
}

void imprime_exames_aluno(Lista_Alunos lista_principal_alunos,Lista_Exames lista_principal_exames){
    Aluno* aluno;
    Lista_Exames le_sec;
    Lista_Alunos la_aux;

    la_aux = lista_principal_alunos;
    aluno = escolhe_aluno(la_aux);
    if(aluno==NULL)
        return;
    while(aluno != la_aux->aluno)
        la_aux=la_aux->next;
    system("cls");

    le_sec=la_aux->exames;
    if(le_sec->next==NULL){
        printf("O aluno não está inscrito em nenhum exame.\n");
        return;
    }
    printf("Lista de exames deste aluno:\n");
    while(le_sec->next!=NULL){
        le_sec=le_sec->next;
        imprime_exames(lista_principal_exames,le_sec->exame);
    }
}

void criar_disciplina(Lista_Disciplinas lista_principal_disciplinas,char*nome,char*docente_responsavel){
    Disciplina * disciplina = (Disciplina *)malloc(sizeof(Disciplina));
    if(disciplina==NULL)
        printf("Erro na alocação de memória.\n");
    disciplina->nome = malloc(sizeof(char)*MAX_STRING);
    disciplina->docente_responsavel = malloc(sizeof(char)*MAX_STRING);
    strcpy(disciplina->nome,nome);
    strcpy(disciplina->docente_responsavel,docente_responsavel);

    insere_lista_principal_disciplinas(lista_principal_disciplinas,disciplina);
    free(nome);
    free(docente_responsavel);
}

void criar_disciplina_manual(Lista_Disciplinas lista_principal_disciplinas){
    char*nome;
    char*docente_responsavel;
    printf("Nome: ");
    nome = devolve_nome();
    printf("Docente Responsavel: ");
    docente_responsavel = devolve_nome();

    criar_disciplina(lista_principal_disciplinas,nome,docente_responsavel);
}

void altera_disciplina(Lista_Disciplinas lista_disciplinas){
    int indicador;
    Disciplina* aux;

    printf("Escolha a disciplina: \n");
    aux = escolhe_disciplina(lista_disciplinas);
    if (aux==NULL)
        return;
    printf("Que dado pretende alterar?\n");
    printf("[1] Nome da disciplina\n[2] Docente Responsável\n");
    indicador = devolve_inteiro();
    switch(indicador){
        case 1:
            printf("Introduza o novo nome da disciplina: ");
            aux->nome = devolve_nome();
            break;
        case 2:
            printf("Introduza o nome do novo docente responsável: ");
            aux->docente_responsavel=devolve_nome();
            break;
        default:
            printf("Opção inválida. Introduza de novo: ");
    }
        printf("Disciplina alterada com sucesso!\n");
}

void apagar_disciplina(Lista_Disciplinas lista_disciplinas){
    Disciplina *aux_d;

    aux_d=escolhe_disciplina(lista_disciplinas);
    if(aux_d==NULL)
        return;
    elimina_lista_disciplinas(lista_disciplinas,aux_d);
}

void criar_exame(Lista_Exames lista_principal_exames,Data* data, Hora* hora, Duracao* duracao, char*epoca,char*disciplina,Sala*sala){
    Lista_Exames le_aux;
    Lista_Salas novo;
    Exame* exame = (Exame*)malloc(sizeof(Exame));
    if(exame==NULL)
        printf("Erro na alocação de memória.\n");
    exame->epoca = malloc(sizeof(char)*MAX_STRING);
    exame->disciplina = malloc(sizeof(char)*MAX_STRING);
    exame->data=data;
    exame->hora=hora;
    exame->duracao=duracao;
    strcpy(exame->epoca,epoca);
    exame->sala=sala;
    strcpy(exame->disciplina,disciplina);

    insere_lista_principal_exames(lista_principal_exames,exame);
    le_aux=lista_principal_exames->next;
    while(le_aux->exame!=exame)
        le_aux=le_aux->next;
    while(le_aux->salas->next!=NULL)
        le_aux->salas=le_aux->salas->next;

    novo = cria_lista_salas();
    novo->sala=sala;
    while(le_aux->salas->next!=NULL)
        le_aux=le_aux->next;
    le_aux->salas->next=novo;

    free(epoca);
    free(disciplina);
}

void criar_exame_manual(Lista_Exames lista_principal_exames){
    Data * data = (Data*)malloc(sizeof(Data));
    Hora * hora = (Hora*)malloc(sizeof(Hora));
    Duracao * duracao = (Duracao*)malloc(sizeof(Duracao));
    Sala * sala = (Sala*)malloc((sizeof(Sala)));
    char * epoca;
    char * disciplina;
    int invalido,invalidos;
    Lista_Exames le_aux;
    le_aux = lista_principal_exames->next;
    if(data==NULL || hora == NULL || duracao == NULL || sala == NULL)
        printf("Erro na alocação de memória.\n");
    printf("Disciplina: ");
    disciplina=devolve_nome();
    do{
    printf("Época: ");
    epoca=devolve_nome();
    invalido = verifica_epoca(epoca);
    if (invalido==0)
        printf("Introduza uma época válida!\n");
    }while(invalido==0);

    printf("Introduza a data do exame:\n");
    do{
    printf("Ano: ");
    data->ano=devolve_inteiro();
    printf("Mês: ");
    data->mes=devolve_inteiro();
    printf("Dia: ");
    data->dia=devolve_inteiro();
    invalido = verifica_data(data);
    if(invalido==0)
        printf("Data inválida. Introduza a data novamente!\n");
    else if(data->ano > 9999)
        printf("Apenas permitidas datas até ao ano 9999. Introduza a data novamente!\n");
    }while(invalido==0 || data->ano > 9999);

    printf("Introduza a hora do exame:\n");
    do{
    printf("Hora: ");
    hora->hora=devolve_inteiro();
    printf("Minutos: ");
    hora->minutos=devolve_inteiro();
    invalido = verifica_hora(hora);
    if(invalido==0)
        printf("Hora inválida. Introduza novamente a hora!\n");
    }while(invalido==0);

    printf("Introduza a duração do exame:\n");
    do{
    printf("Horas: ");
    duracao->horas=devolve_inteiro();
    printf("Minutos: ");
    duracao->minutos=devolve_inteiro();
    if(duracao->minutos < 0 || duracao->minutos > 59 || (duracao->horas == 0 && duracao->minutos == 0))
        printf("Introduza uma duração válida!\n");
    }while(duracao->minutos < 0 || duracao->minutos > 59 || (duracao->horas == 0 && duracao->minutos == 0));

    printf("Introduza o nome da sala:\n");
    printf("Nome: ");
    sala->nome=devolve_nome();
    do{
    printf("Vagas: ");
    sala->vagas=devolve_inteiro();
    if(sala->vagas > 30)
        printf("Introduza um número de vagas válido (cada sala tem apenas 30 lugares)!\n");
    }while(sala->vagas>30);

    do{
        invalidos = verifica_salas(le_aux,sala->nome,data,hora,duracao);
        if(invalidos == 0){
            do{
                printf("Hora: ");
                hora->hora=devolve_inteiro();
                printf("Minutos: ");
                hora->minutos=devolve_inteiro();
                invalido = verifica_hora(hora);
                if(invalido==0)
                    printf("Hora inválida. Introduza novamente a hora!\n");
                }while(invalido==0);
    }
    if(invalidos==1){
        le_aux=le_aux->next;
    }
    }while(le_aux!=NULL);

    criar_exame(lista_principal_exames,data,hora,duracao,epoca,disciplina,sala);
    printf("Exame criado com sucesso!\n");
}

void altera_exame(Lista_Exames lista_exames){
    Exame * aux;
    char* sala;
    Hora* hora = (Hora*)malloc(sizeof(Hora));
    Lista_Exames le_aux;
    int opcao,invalidos;
    int invalido = 0;
    le_aux=lista_exames->next;

    printf("Escolha o exame que pretende alterar: \n");
    aux = escolhe_exame(lista_exames);
    if(aux==NULL)
        return;
    printf("Qual a informação que pretende alterar?\n");
    printf("[1] Disciplina\n[2] Época\n[3] Data\n[4] Hora\n[5] Duração\n[6] Sala\n[7] Vagas\n");
    opcao = devolve_inteiro();

    switch(opcao){
        case 1:
            printf("Introduza a nova disciplina do exame.");
            aux->disciplina=devolve_nome();
            break;
        case 2:
            printf("Introduza a nova época do exame: ");
            aux->epoca=devolve_nome();
            break;
        case 3:
            printf("Introduza a data do exame:\n");
            do{
            printf("Ano: ");
            aux->data->ano=devolve_inteiro();
            printf("Mês: ");
            aux->data->mes=devolve_inteiro();
            printf("Dia: ");
            aux->data->dia=devolve_inteiro();
            invalido = verifica_data(aux->data);
            if(invalido==0)
                printf("Data inválida. Introduza a data novamente!\n");
            else if(aux->data->ano > 9999)
                printf("Apenas permitidas datas até ao ano 9999. Introduza a data novamente!\n");
            }while(invalido==0 || aux->data->ano > 9999);
            break;

        case 4:
            printf("Introduza a nova hora do exame:\n");
            do{
                printf("Hora: ");
                hora->hora=devolve_inteiro();
                printf("Minutos: ");
                hora->minutos=devolve_inteiro();
                invalido = verifica_hora(hora);
                if(invalido==0)
                    printf("Hora inválida. Introduza novamente a hora!\n");
                }while(invalido==0);
                do{
        invalidos = verifica_salas(le_aux,sala,aux->data,hora,aux->duracao);
        if(invalidos == 0){
            printf("Introduza o nome da nova sala: ");
           sala=devolve_nome();
        }
        else{
            le_aux=le_aux->next;
        }
    }while(le_aux!=NULL);
        if(invalidos==1)
            aux->hora=hora;
        if(sala!=aux->sala->nome)
            strcpy(aux->sala->nome,sala);
                break;
        case 5:
            printf("Introduza a nova duração do exame:\n");
            do{
                printf("Horas: ");
                aux->duracao->horas=devolve_inteiro();
                printf("Minutos: ");
                aux->duracao->minutos=devolve_inteiro();
                if(aux->duracao->minutos < 0 || aux->duracao->minutos > 59)
                    printf("Introduza uma duração válida!\n");
                }while(aux->duracao->minutos < 0 || aux->duracao->minutos > 59);
                break;
        case 6:
            printf("Introduza o novo nome da sala: ");
            sala=devolve_nome();
            do{
        invalidos = verifica_salas(le_aux,sala,aux->data,aux->hora,aux->duracao);
        if(invalidos == 0){
            printf("Introduza o novo nome da sala: ");
           sala=devolve_nome();
        }
        else{
            le_aux=le_aux->next;
        }
    }while(le_aux!=NULL);
        if(invalidos==1)
            strcpy(aux->sala->nome,sala);
        break;
        case 7:
            printf("Introduza o novo número de vagas: ");
            aux->sala->vagas=devolve_inteiro();
            break;
        default:
            printf("Opção inválida. Introduza de novo: ");
    }
    printf("Exame alterado com sucesso!\n");
}

void apagar_exame(Lista_Exames lista_exames){
    Exame* aux_e;
    Aluno* aux_a;
    Lista_Alunos la_sec;
    Lista_Exames le_aux,le_sec;

    aux_e=escolhe_exame(lista_exames);
    if(aux_e==NULL)
        return;

    le_aux=lista_exames->next;
    while(le_aux->exame!=aux_e){
        le_aux=le_aux->next;
    }

    elimina_lista_exames(lista_exames,aux_e);
}

void desinscreve_aluno_exame(Lista_Exames lista_principal_exames,Lista_Alunos lista_principal_alunos){
    Exame* aux_e;
    Aluno* aux_a;
    Lista_Alunos node_a,la_aux,la_sec;
    Lista_Exames node_e,le_aux,le_sec;
    int aux;

    aux_a=escolhe_aluno(lista_principal_alunos);
    if(aux_a==NULL)
        return;

    aux_e=escolhe_exame(lista_principal_exames);
    if(aux_e==NULL)
        return;

    la_aux=lista_principal_alunos->next;
    le_aux=lista_principal_exames->next;

    while(aux_a!=la_aux->aluno)
        la_aux=la_aux->next;
    while(aux_e!=le_aux->exame)
        le_aux=le_aux->next;

    aux = procura_aluno_de_exame(le_aux,aux_a);
    if(aux==1){
        node_a = cria_lista_alunos();
        node_a->aluno = la_aux->aluno;

        node_e = cria_lista_exames();
        node_e->exame = le_aux->exame;

        la_sec=le_aux->alunos;
        while(la_sec->next->aluno != aux_a)
            la_sec=la_sec->next;
        la_sec->next=NULL;

        le_sec=la_aux->exames;
        while(le_sec->next->exame != aux_e)
            le_sec=le_sec->next;
        le_sec->next=NULL;

        (aux_e->sala->vagas)=(aux_e->sala->vagas)+1;
        printf("Aluno desinscrito do exame com sucesso.\n");
        return;

    }
    else{
        printf("O aluno não está inscrito neste exame.\n");
    }
}
void insere_aluno_exame(Lista_Exames lista_principal_exames,Lista_Disciplinas lista_principal_disciplinas,Lista_Alunos lista_principal_alunos){
    Exame* aux_e;
    Disciplina* aux_d;
    Aluno* aux_a;
    Lista_Alunos node_a,la_aux,la_sec;
    Lista_Disciplinas node_d,ld_aux,ld_sec;
    Lista_Exames node_e,le_aux,le_sec,novo;
    Lista_Salas nova_sala,ls_sec;
    Sala* sala = (Sala*)malloc(sizeof(Sala));
    int aux,opcao;
    Exame* exame = (Exame*)malloc(sizeof(Exame));


    aux_a=escolhe_aluno(lista_principal_alunos);
    if(aux_a==NULL)
        return;

    aux_d=escolhe_disciplina(lista_principal_disciplinas);
    if(aux_d==NULL)
        return;

    aux_e=escolhe_exame(lista_principal_exames);
    if(aux_e==NULL)
        return;

    le_aux=lista_principal_exames->next;
    la_aux=lista_principal_alunos->next;
    ld_aux=lista_principal_disciplinas->next;
    ls_sec=le_aux->salas;

    if(aux_e->sala->vagas == 0){
            printf("Não existem vagas disponíveis nessa sala para esse exame. Pretende reservar mais uma sala?\n[1] Sim\n[2] Não\n");
            opcao=devolve_inteiro();
            if(opcao==1){
                nova_sala=cria_lista_salas();
                printf("Nome da sala: ");
                sala->nome=devolve_nome();
                sala->vagas=30;
                nova_sala->sala=sala;
                while(ls_sec->next!=NULL)
                    ls_sec=ls_sec->next;
                ls_sec->next=nova_sala;
                aux_e->sala->vagas=(aux_e->sala->vagas)+30;
                }
            else
                return;
        }

    while(aux_a!=la_aux->aluno)
        la_aux=la_aux->next;
    while(aux_d!=ld_aux->disciplina)
        ld_aux=ld_aux->next;
    while(aux_e!=le_aux->exame)
        le_aux=le_aux->next;

    aux = procura_aluno_de_exame(le_aux,aux_a);
    if(aux==1){
        printf("Aluno já inscrito nesse exame.\n");
        return;
    }
    else{
        node_a = cria_lista_alunos();
        node_a->aluno = la_aux->aluno;

        node_d = cria_lista_disciplinas();
        node_d->disciplina = ld_aux->disciplina;

        node_e = cria_lista_exames();
        node_e->exame = le_aux->exame;

        la_sec=le_aux->alunos;
        while(la_sec->next != NULL)
            la_sec=la_sec->next;
        la_sec->next=node_a;

        le_sec=la_aux->exames;
        while(le_sec->next != NULL)
            le_sec=le_sec->next;
        le_sec->next=node_e;

        le_sec=ld_aux->exames;
        while(le_sec->next != NULL)
            le_sec=le_sec->next;
        le_sec->next=node_e;

        (aux_e->sala->vagas)=(aux_e->sala->vagas)-1;
        printf("Aluno inscrito no exame com sucesso.\n");
        return;
    }
}

void imprime_lista_exames(Lista_Exames lista_principal_exames){
    Lista_Exames le_aux;
    le_aux = lista_principal_exames->next;

    if(le_aux==NULL){
        printf("Não existem exames na base de dados.\n");
        return;
    }
    while(le_aux!=NULL){
        imprime_exames(le_aux,le_aux->exame);
        le_aux=le_aux->next;
    }
}

void imprime_alunos_exame(Lista_Exames lista_principal_exames){
    Exame* exame;
    Lista_Alunos la_sec;
    Lista_Exames le_aux;

    le_aux = lista_principal_exames;
    exame = escolhe_exame(le_aux);
    if(exame==NULL)
        return;
    while(exame != le_aux->exame)
        le_aux=le_aux->next;
    system("cls");

    la_sec=le_aux->alunos;
    if(la_sec->next==NULL){
        printf("Não existem alunos inscritos neste exame.\n");
        return;
    }
    printf("Lista de alunos deste exame:\n");
    while(la_sec->next!=NULL){
        la_sec=la_sec->next;
        imprime_alunos(la_sec->aluno);
    }
}

int procura_sala_de_exame(Lista_Exames lista_exames,char*nome_sala,int aux, Exame* aux_e){
    Lista_Exames percorre_exames;
    Lista_Salas percorre_salas;
    percorre_exames=lista_exames;
    percorre_salas=lista_exames->salas;
    while(percorre_exames->next!=NULL){
        percorre_exames=percorre_exames->next;
        if(strcmp(percorre_salas->next->sala->nome,nome_sala)!=0){
            percorre_salas=percorre_salas->next;
        }
        else{
                percorre_salas=percorre_salas->next;
                break;
        }
    }
    if(strcmp(percorre_salas->next->sala->nome,nome_sala)==0){
        return 1;
    }
    else{
        return 0;
    }
}

int verifica_salas(Lista_Exames le_aux,char*nome,Data*data,Hora*hora,Duracao*duracao){
    if(le_aux!=NULL){
    int aux = 3;
    int maximo_h;
    int maximo_m;
    Hora* maximo_l;
    Hora* maximo_v;
    maximo_l = (Hora*)malloc(sizeof(Hora));
    maximo_v = (Hora*)malloc(sizeof(Hora));
    maximo_h = (le_aux->exame->hora->hora) + (le_aux->exame->duracao->horas);
    maximo_m = (le_aux->exame->hora->minutos) + (le_aux->exame->duracao->minutos);
    maximo_v->hora = (hora->hora)+(duracao->horas);
    maximo_v->minutos = (hora->minutos)+(duracao->minutos);
    if(maximo_m>59){
        maximo_h++;
        maximo_m=maximo_m-60;
    }
    else if(maximo_v->minutos>59){
        maximo_v->hora++;
        maximo_v->minutos=maximo_v->minutos-60;
    }
    maximo_l->hora=maximo_h;
    maximo_l->minutos=maximo_m;
    aux = procura_sala_de_exame(le_aux,nome,aux,le_aux->exame);
    if(aux==1){
            if(le_aux->exame->data->dia == data->dia && le_aux->exame->data->mes == data->mes && le_aux->exame->data->ano == data->ano){
                if((compara_datas(le_aux->exame->data,data,hora,le_aux->exame->hora)==-1 && (compara_datas(le_aux->exame->data,data,le_aux->exame->hora,maximo_v)==-1 && compara_datas(le_aux->exame->data,data,maximo_v,maximo_l)==-1)) || (compara_datas(le_aux->exame->data,data,le_aux->exame->hora,hora)!=1 && compara_datas(le_aux->exame->data,data,hora,maximo_l)==-1) || (compara_datas(le_aux->exame->data,data,hora,le_aux->exame->hora)==-1 && compara_datas(le_aux->exame->data,data,maximo_l,maximo_v)!=1)){
                    printf("Há um exame a decorrer nessa sala desde as %02d:%02d até às %02d:%02d. Introduza uma nova hora: \n",le_aux->exame->hora->hora,le_aux->exame->hora->minutos,maximo_h,maximo_m);
                    return 0;
                }
                else
                    return 1;
                }
            else
                return 1;
            }
    else{
        return 1;
    }
    }
    else
        return 2;
}

void menu_alunos(Lista_Alunos lista_principal_alunos,Lista_Exames lista_principal_exames){
    int opcao;
    printf("[1] Criar dados de aluno.\n");
    printf("[2] Alterar dados de aluno.\n");
    printf("[3] Apagar dados de aluno.\n");
    printf("[4] Listar exames em que um aluno esta inscrito.\n");
    opcao = devolve_inteiro();
    system("cls");

    switch(opcao){
    case 1:
        criar_aluno_manual(lista_principal_alunos);
        printf("Aluno criado com sucesso!\n\n");
        break;
    case 2:
        alterar_aluno(lista_principal_alunos);
        break;
    case 3:
        apagar_aluno(lista_principal_alunos);
        break;
    case 4:
        imprime_exames_aluno(lista_principal_alunos,lista_principal_exames);
        break;
    default:
        system("cls");
        printf("Introduza uma opcao valida!\n");
        menu_alunos(lista_principal_alunos,lista_principal_exames);
    }
}

void menu_disciplinas(Lista_Disciplinas lista_principal_disciplinas){
    int opcao;
    printf("[1] Criar dados de disciplina.\n");
    printf("[2] Alterar dados de disciplina.\n");
    printf("[3] Apagar dados de disciplina.\n");
    printf("[4] Listar exames de uma disciplina.\n");
    opcao = devolve_inteiro();
    system("cls");

    switch(opcao){
    case 1:
        criar_disciplina_manual(lista_principal_disciplinas);
        printf("Disciplina criada com sucesso!\n");
        break;
    case 2:
        altera_disciplina(lista_principal_disciplinas);
        break;
    case 3:
        apagar_disciplina(lista_principal_disciplinas);
        break;
    case 4:
        imprime_exames_disciplina(lista_principal_disciplinas);
        break;
    default:
        system("cls");
        printf("Introduza uma opcao valida!\n\n");
        menu_disciplinas(lista_principal_disciplinas);
    }
}

void menu_exames(Lista_Exames lista_principal_exames,Lista_Disciplinas lista_principal_disciplinas, Lista_Alunos lista_principal_alunos){
    int opcao;
    printf("[1] Criar exame.\n");
    printf("[2] Alterar exame.\n");
    printf("[3] Apagar exame.\n");
    printf("[4] Inscrever um aluno num exame.\n");
    printf("[5] Desinscrever aluno de um exame.\n");
    printf("[6] Listar exames.\n");
    printf("[7] Listar alunos inscritos num exame.\n");
    opcao = devolve_inteiro();
    system("cls");

    switch(opcao){
    case 1:
        criar_exame_manual(lista_principal_exames);
        break;
    case 2:
        altera_exame(lista_principal_exames);
        break;
    case 3:
        apagar_exame(lista_principal_exames);
        break;
    case 4:
        insere_aluno_exame(lista_principal_exames,lista_principal_disciplinas,lista_principal_alunos);
        break;
    case 5:
        desinscreve_aluno_exame(lista_principal_exames,lista_principal_alunos);
        break;
    case 6:
        imprime_lista_exames(lista_principal_exames);
        break;
    case 7:
        imprime_alunos_exame(lista_principal_exames);
        break;
    default:
        system("cls");
        printf("Introduza uma opcao valida!\n");
        menu_exames(lista_principal_exames,lista_principal_disciplinas,lista_principal_alunos);
    }
}
