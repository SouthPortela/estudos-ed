#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#define MAX_DISTINCT_PALAVRAS 15000
#define TAM_PALAVRA 100
#define MAX_LINE 1024

// Estrutura para armazenar a palavra e sua frequência
typedef struct {
    char Termo[TAM_PALAVRA];
    int Ocorrencias;
} PalavraChave;

/**
 * Função para remover espaços e converter para minúsculas.
 * Padroniza os tokens para garantir contagem correta.
 */
void normalizar(char *str) {
    char *dest = str;
    char *src = str;

    // Remove espaços no início
    while (isspace((unsigned char)*src)) src++;
    
    while (*src) {
        *dest = tolower((unsigned char)*src);
        dest++;
        src++;
    }
    *dest = '\0';

    // Remove espaços no fim
    if (dest > str) {
        dest--;
        while (dest >= str && isspace((unsigned char)*dest)) {
            *dest = '\0';
            dest--;
        }
    }
}
// ==============================
// BUSCA BINARIA
// ==============================
static int busca_binaria(char *Palavra, int Esquerda, int Direita, PalavraChave *Lista){
    int Meio;
    if (Esquerda > Direita)
        return -1;//nao encontrado
    else {
        int Meio = (Esquerda + Direita) / 2;
        int cmp = strcmp(Palavra, Lista[Meio].Termo);

        if (cmp == 0){
            return Meio;
        } else if (cmp < 0){
            return busca_binaria(Palavra, Esquerda, Meio - 1, Lista);
        }else{
            return busca_binaria(Palavra, Meio + 1, Direita, Lista);
        }
    }
}

/**
 * Função de comparação para o qsort (ordem alfabética).
 */
int comparar_alfabetico(const void *a, const void *b) {
    PalavraChave *p1 = (PalavraChave *)a;
    PalavraChave *p2 = (PalavraChave *)b;
    return strcmp(p1->Termo, p2->Termo);
}

int main() {
    PalavraChave Lista[MAX_DISTINCT_PALAVRAS];
    int TotalDistintas = 0;

    FILE *Arquivo = fopen("savedrecs_total.txt", "r");
    if (Arquivo == NULL) {
        printf("Erro: savedrecs_total.txt nao encontrado.\n");
        return 1;
    }

    char Linha[MAX_LINE];
    while (fgets(Linha, sizeof(Linha), Arquivo)) {
        // As fontes identificam palavras-chave pela etiqueta DE
        if (strncmp(Linha, "DE ", 3) == 0) {
            char *Conteudo = Linha + 3;
            // Tokens separados por ponto e vírgula conforme os registros
            char *Token = strtok(Conteudo, ";\n");

            while (Token != NULL) {
                char Temp[TAM_PALAVRA];
                strncpy(Temp, Token, TAM_PALAVRA - 1);
                Temp[TAM_PALAVRA - 1] = '\0';
                
                normalizar(Temp);

                if (strlen(Temp) > 0) {
                    // 1. Tenta achar a palavra usando a busca binária
                    int indice = busca_binaria(Temp, 0, TotalDistintas - 1, Lista);

                    if (indice != -1) {
                        // A palavra já existe, apenas incrementa a contagem
                        Lista[indice].Ocorrencias++;
                    } else if (TotalDistintas < MAX_DISTINCT_PALAVRAS) {
                        // 2. A palavra não existe. 
                        // Descobrimos onde inseri-la empurrando elementos maiores para frente.
                        int pos = TotalDistintas - 1;

                        while (pos >= 0 && strcmp(Lista[pos].Termo, Temp) > 0) {
                            Lista[pos + 1] = Lista[pos];
                            pos--;
                        }

                        // 3. Insere a nova palavra na posição que foi liberada
                        strcpy(Lista[pos + 1].Termo, Temp);
                        Lista[pos + 1].Ocorrencias = 1;
                        TotalDistintas++;
                    }
                }
                Token = strtok(NULL, ";\n");
            }
        }
    }
    fclose(Arquivo);

    // Ordenação da Lista de structs
    qsort(Lista, TotalDistintas, sizeof(PalavraChave), comparar_alfabetico);

    // Exibição do resultado final
    printf("%-40s | %s\n", "PALAVRA-CHAVE (ORDENADA)", "OCORRENCIAS");
    printf("-----------------------------------------|------------\n");
    for (int i = 0; i < TotalDistintas; i++) {
        printf("%-40s | %d\n", Lista[i].Termo, Lista[i].Ocorrencias);
    }
    printf("\n Total de palavras distintas: %d\n", TotalDistintas );
    char Palavra[TAM_PALAVRA];
    printf("\n Escreva a palavra para realizar a busca: ");
    fgets(Palavra, TAM_PALAVRA, stdin);
    normalizar(Palavra);
    printf("Indice: %i\n", busca_binaria(Palavra, 0, TotalDistintas - 1, Lista));


    return 0;
}
