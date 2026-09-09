#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

#define BUFFER 4096
#define TAM_PALAVRA 100


typedef struct Node{

    char Palavra[TAM_PALAVRA];
    int Quant;

    struct Node *Prox;
    struct Node *Ant;

}Node;



// ==============================
// NORMALIZA PALAVRA
// ==============================

void normalizar(char *str){

    int i;


    // minusculo
    for(i = 0; str[i]; i++){
        str[i] = tolower((unsigned char)str[i]);
    }


    // remove espaço começo
    while(isspace((unsigned char)*str)){
        memmove(str, str+1, strlen(str));
    }


    // remove espaço final

    int tam = strlen(str);

    while(tam > 0 && isspace((unsigned char)str[tam-1])){

        str[tam-1] = '\0';
        tam--;

    }

}



// ==============================
// CRIA NO
// ==============================

Node* criarNo(char *Palavra){

    Node *novo = malloc(sizeof(Node));


    if(novo == NULL)
        return NULL;



    strcpy(novo->Palavra, Palavra);

    novo->Quant = 1;


    // circular

    novo->Prox = novo;
    novo->Ant = novo;


    return novo;

}



// ==============================
// INSERE OU INCREMENTA
// ==============================

void inserirOuIncrementar(Node **Cabeca, char *Palavra){


    if(*Cabeca == NULL){

        *Cabeca = criarNo(Palavra);

        return;
    }



    Node *Atual = *Cabeca;



    do{


        if(strcmp(Atual->Palavra, Palavra) == 0){

            Atual->Quant++;

            return;

        }



        Atual = Atual->Prox;


    }while(Atual != *Cabeca);




    // não encontrou, cria novo

    Node *novo = criarNo(Palavra);



    Node *ultimo = (*Cabeca)->Ant;



    ultimo->Prox = novo;

    novo->Ant = ultimo;


    novo->Prox = *Cabeca;

    (*Cabeca)->Ant = novo;



}



// ==============================
// IMPRIME REVERSO
// ==============================

void imprimirListaReversa(Node *Cabeca){


    if(Cabeca == NULL)
        return;



    Node *Atual = Cabeca->Ant;



    do{


        printf("%s (%d)\n",
        Atual->Palavra,
        Atual->Quant);



        Atual = Atual->Ant;



    }while(Atual != Cabeca->Ant);



}



// ==============================
// MAIN
// ==============================

int main(int argc, char *argv[]){



    if(argc < 4){

        printf("Uso: %s saida.txt arquivo1.txt arquivo2.txt...\n",
        argv[0]);

        return 1;

    }



    FILE *saida = fopen(argv[1],"w");



    if(saida == NULL){

        printf("Erro ao criar arquivo\n");

        return 1;

    }



    Node *Alfabeto[26];



    for(int i=0;i<26;i++){

        Alfabeto[i] = NULL;

    }





    char buffer[BUFFER];



    for(int i=2;i<argc;i++){



        FILE *arquivo = fopen(argv[i],"r");



        if(arquivo == NULL){

            continue;

        }



        int linha = 0;



        while(fgets(buffer,BUFFER,arquivo)){



            linha++;



            // pula cabeçalho

            if(linha <= 2)
                continue;



            // fim do arquivo

            if(strncmp(buffer,"EF",2)==0)
                continue;



            // salva no arquivo mesclado

            fputs(buffer,saida);




            // encontrou palavras chave

            if(strncmp(buffer,"DE ",3)==0){



                char *token;



                token = strtok(buffer+3,";\n");



                while(token != NULL){



                    normalizar(token);



                    if(strlen(token)>0 && isalpha(token[0])){


                        int indice = token[0]-'a';



                        if(indice>=0 && indice<26){


                            inserirOuIncrementar(
                                &Alfabeto[indice],
                                token
                            );


                        }


                    }



                    token = strtok(NULL,";\n");

                }



            }



        }



        fclose(arquivo);



    }



    fclose(saida);




    // imprime resultado


    printf("\nPALAVRAS ENCONTRADAS:\n\n");



    for(int i=0;i<26;i++){



        if(Alfabeto[i] != NULL){



            printf("\n[%c]\n",
            'A'+i);



            imprimirListaReversa(
                Alfabeto[i]
            );


        }


    }



    return 0;

}
