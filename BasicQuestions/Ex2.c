#include <stdio.h>
#include <string.h>

#define MAX_SITES 3
#define MAX_URL 50

typedef struct{
  char urls[MAX_SITES][MAX_URL];
  int topo;
} PilhaHistorico;

void inicializar(PilhaHistorico *p){
  p->topo = -1;
}

void acessar(PilhaHistorico *p, char *site){
  if(p->topo == MAX_SITES - 1){
    printf("Historico cheio!\n");
    return;
  }
  p->topo++;

  strcpy(p->urls[p->topo], site);

  printf("Acessou: %s (Valor do topo: %d)\n", site, p->topo);
}

void voltar(PilhaHistorico *p){
  if (p->topo == -1){
    printf("ERRO: Ja esta no inicio, nao tem destino no voltar.\n");
    return;
  }
  p->topo--;
  if (p->topo == -1){
    printf("Voltou para o inicio.\n");
  }else{
    printf("Voltou para: %s\n", p->urls[p->topo]);
  }
}

int main(){
  PilhaHistorico browser;
  inicializar(&browser);

  printf("---- NAVEGANDO ----\n");
  acessar(&browser, "www.youtube.com");
  acessar(&browser, "www.uol.com.br");
  acessar(&browser, "www.instagram.com");
  acessar(&browser, "www.github.com");

  printf("\n----- VOLTAR -----\n");

  voltar(&browser);
  voltar(&browser);
  voltar(&browser);
  voltar(&browser);

  return 0;
}


