#include "header.h"

void verifica_ficheiros(){
	FILE *ficheiro;

	if (access("alunos.txt",F_OK)==-1){
    	ficheiro=fopen("alunos.txt","w");
    	fclose(ficheiro);
	}
	if (access("disciplinas.txt",F_OK)==-1){
    	ficheiro=fopen("disciplinas.txt","w");
    	fclose(ficheiro);
	}
	if (access("exames.txt",F_OK)==-1){
    	ficheiro=fopen("exames.txt","w");
    	fclose(ficheiro);
	}
	if (access("inscricoes.txt",F_OK)==-1){
        ficheiro = fopen("inscricoes.txt","w");
        fclose(ficheiro);
	}
}

void guarda_listas(Lista_Alunos lista_principal_alunos, Lista_Disciplinas lista_principal_disciplinas, Lista_Exames lista_principal_exames){
    Lista_Alunos la_aux,la_sec;
    Lista_Disciplinas ld_aux;
    Lista_Exames le_aux,le_sec;
    FILE *ficheiro;
    int int_aux;

    /* Alunos */
    ficheiro=fopen("alunos.txt", "w");
    la_aux=lista_principal_alunos;
    while(la_aux->next!=NULL){
        la_aux=la_aux->next;
        fprintf(ficheiro, "%01d%10d%s%s/%s", la_aux->aluno->ano_de_matricula,la_aux->aluno->numero_de_estudante, la_aux->aluno->curso, la_aux->aluno->regime, la_aux->aluno-> nome);
        if(la_aux->next!=NULL)
            fprintf(ficheiro, "\n");
    }
    fclose(ficheiro);

    /*Disciplinas*/
    ficheiro=fopen("disciplinas.txt", "w");
    ld_aux=lista_principal_disciplinas;
    while(ld_aux->next!=NULL){
        ld_aux=ld_aux->next;
        fprintf(ficheiro, "%s/%s",ld_aux->disciplina->docente_responsavel, ld_aux->disciplina->nome);
        if(ld_aux->next!=NULL)
            fprintf(ficheiro, "\n");
    }
    fclose(ficheiro);

    /*Exames*/
    ficheiro=fopen("exames.txt", "w");
    le_aux=lista_principal_exames;
    while(le_aux->next!=NULL){
        le_aux=le_aux->next;
        fprintf(ficheiro, "%02d%02d%04d%02d%02d%02d%02d%02d%s/%s/%s",le_aux->exame->data->dia,le_aux->exame->data->mes,le_aux->exame->data->ano,le_aux->exame->hora->hora,le_aux->exame->hora->minutos,le_aux->exame->duracao->horas,le_aux->exame->duracao->minutos,le_aux->exame->sala->vagas,le_aux->exame->sala->nome,le_aux->exame->epoca,le_aux->exame->disciplina);
        if(le_aux->next!=NULL)
            fprintf(ficheiro, "\n");
    }
    fclose(ficheiro);


    /*Inscrições*/
    ficheiro=fopen("inscricoes.txt","w");

    /*pela lista de exame*/
    le_aux=lista_principal_exames;
    while(le_aux->next!=NULL){
        le_aux=le_aux->next;
        la_sec=le_aux->alunos;
        while(la_sec->next!=NULL){
            la_sec=la_sec->next;
            int_aux=encontra_posicao_aluno(lista_principal_alunos,la_sec->aluno);
            fprintf(ficheiro, "%d", int_aux);
            if(la_sec->next!=NULL)
                fprintf(ficheiro,"|");
        }
        fprintf(ficheiro, "\n");
    }
    /*pela lista de alunos*/

    la_aux=lista_principal_alunos;
    if(la_aux->next!=NULL)
        fprintf(ficheiro,"#\n");
    while(la_aux->next!=NULL){
        la_aux=la_aux->next;
        le_sec=la_aux->exames;
        while(le_sec->next!=NULL){
            le_sec=le_sec->next;
            int_aux=encontra_posicao_exame(lista_principal_exames,le_sec->exame);
            fprintf(ficheiro,"%d",int_aux);
            if(le_sec->next!=NULL)
                fprintf(ficheiro,"|");
        }
        if(la_aux->next!=NULL)
            fprintf(ficheiro, "\n");
    }

    fclose(ficheiro);

}


void carrega_listas(Lista_Alunos lista_principal_alunos,Lista_Disciplinas lista_principal_disciplinas, Lista_Exames lista_principal_exames){
    Lista_Alunos la_aux, node_a, la_sec;
    Lista_Exames le_aux, node_e, le_sec;
    FILE *ficheiro;
    char linha[MAX_STRING],copia[MAX_STRING];
    int n_estudante = 0;
    int ano_de_matricula = 0;
    int int_aux;
    Data * data;
    Hora * hora;
    Sala * sala;
    Duracao * duracao;
    char * aux_regime;
    char * aux_nome;
    char * aux_disciplina;
    char * aux_docente;
    char * epoca;
    char * sala_aux;
    char * aux_epoca;
    char * disciplina;
    char * docente;
    char * curso = '\0';
    char *  regime = '\0';
    char * nome_aluno = '\0';
    char * char_aux;

/*Alunos*/
    ficheiro=fopen("alunos.txt","r");
    while(fgets(linha,MAX_STRING,ficheiro)!=NULL){

            strncpy(copia,linha,1);
            copia[1]='\0';
            ano_de_matricula=atoi(copia);

            strncpy(copia,linha+1,10);
            copia[10]='\0';
            n_estudante=atoi(copia);

            strncpy(copia,linha+11,3);
            copia[3]='\0';
            curso=strdup(copia);

            strcpy(copia,linha+14);
            retira_enter(copia);
            strdup(copia);

            regime=strtok(copia,"/");
            nome_aluno=strtok(NULL,"/");

            aux_regime = strdup(regime);
            aux_nome = strdup(nome_aluno);


            criar_aluno(lista_principal_alunos,aux_nome,curso,aux_regime,ano_de_matricula,n_estudante);
            }
    fclose(ficheiro);

/*Disciplinas*/
    ficheiro = fopen("disciplinas.txt","r");

    while(fgets(linha,MAX_STRING,ficheiro)!=NULL){


            disciplina=strtok(linha,"/");
            docente=strtok(NULL,"/");

            aux_disciplina = strdup(disciplina);
            aux_docente = strdup(docente);

            criar_disciplina(lista_principal_disciplinas,aux_disciplina,aux_docente);

    }
    fclose(ficheiro);

/*Exame*/

    ficheiro = fopen("exames.txt","r");

    while(fgets(linha,MAX_STRING,ficheiro)!=NULL){
        data = (Data*)malloc(sizeof(Data));
        hora = (Hora*)malloc(sizeof(Hora));
        duracao = (Duracao*)malloc(sizeof(Duracao));
        sala = (Sala*)malloc(sizeof(Sala));
        if(data == NULL || hora == NULL || duracao == NULL || sala == NULL)
            printf("Erro na alocação de memória.\n");

        strncpy(copia,linha,2);
        copia[2]='\0';
        data->dia=atoi(copia);

        strncpy(copia,linha+2,2);
        copia[2]='\0';
        data->mes=atoi(copia);

        strncpy(copia,linha+4,4);
        copia[4]='\0';
        data->ano=atoi(copia);

        strncpy(copia,linha+8,2);
        copia[2]='\0';
        hora->hora=atoi(copia);

        strncpy(copia,linha+10,2);
        copia[2]='\0';
        hora->minutos=atoi(copia);

        strncpy(copia,linha+12,2);
        copia[2]='\0';
        duracao->horas=atoi(copia);

        strncpy(copia,linha+14,2);
        copia[2]='\0';
        duracao->minutos=atoi(copia);

        strncpy(copia,linha+16,2);
        copia[2]='\0';
        sala->vagas=atoi(copia);

        strcpy(copia,linha+18);
        retira_enter(copia);
        strdup(copia);

        sala_aux=strtok(copia,"/");
        epoca=strtok(NULL,"/");
        disciplina=strtok(NULL,"/");

        sala->nome = strdup(sala_aux);
        aux_epoca = strdup(epoca);
        aux_disciplina = strdup(disciplina);

        criar_exame(lista_principal_exames,data,hora,duracao,aux_epoca,aux_disciplina,sala);
    }
    fclose(ficheiro);

/*Inscrições*/

    ficheiro=fopen("inscricoes.txt","r");

    int_aux=1;
    la_aux=lista_principal_alunos;
    le_aux=lista_principal_exames;

    while(fgets(linha,MAX_STRING,ficheiro)!=NULL){
        retira_enter(linha);
        if(*linha=='#')
            int_aux=0;

        else if(int_aux){
            le_aux=le_aux->next;

            la_sec=le_aux->alunos;
            char_aux = strtok(linha,"|");
            while(char_aux != NULL){
                node_a = cria_lista_alunos();
                node_a->aluno=aluno_por_posicao(lista_principal_alunos,atoi(char_aux));
                la_sec->next=node_a;
                la_sec=la_sec->next;
                char_aux = strtok(NULL,"|");
            }
        }

        else{
            la_aux=la_aux->next;

            le_sec=la_aux->exames;
            char_aux = strtok(linha,"|");
            while(char_aux!=NULL){
                node_e = cria_lista_exames();
                node_e->exame = exame_por_posicao(lista_principal_exames,atoi(char_aux));
                le_sec->next=node_e;
                le_sec=le_sec->next;
                char_aux = strtok(NULL,"|");
            }
        }
    }
    fclose(ficheiro);
}
