#include <stdio.h>
#include <stdlib.h>
#define TAM 5

typedef struct{
  int Array[TAM];
  int Topo;
} Pilha;

void inicializar(Pilha *p){
  p->Topo = -1;
}

void push(Pilha *p, int Valor){
  if(p->Topo >= TAM -1){
    printf("ERRO: Topo maximo da pilha.\n");
    return;
  }
  p->Topo++;
  p->Array[p->Topo] = Valor;
  printf("Valor do inteiro: %d(posicao da pilha: %d)\n", p->Array[p->Topo], p->Topo);
  
}

void pop(Pilha *p){
  if(p->Topo == -1){
    printf("Pilha vazia, nenhuma mudanca foi feita\n");
    return;
  }
  p->Topo--;
  if(p->Topo == -1){
    printf("Voltou para o inicio.\n");
  }else{
    printf("Voltou para %d\n", p->Array[p->Topo]);
  }
}

int main(){
  Pilha *Ptr = malloc(sizeof(Pilha));
  inicializar(Ptr);
  
  printf("----PREENCHENDO----\n\n\n");
  push(Ptr, 10);
  push(Ptr, 20);
  push(Ptr, 30);
  push(Ptr, 40);
  push(Ptr, 50);
  push(Ptr, 60);

  printf("----REMOVENDO----\n\n\n");
  pop(Ptr);
  pop(Ptr);
  pop(Ptr);
  pop(Ptr);
  pop(Ptr);
  pop(Ptr);
  free(Ptr);
  return 0;
}

