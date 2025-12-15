#include <stdio.h>
#include <locale.h>

int main(){
	setlocale(LC_ALL,"Portuguese");
	int Num=90;
	int *Ptr;
	Ptr = &Num;
	printf("Endereço da variavel Num: %p\n", &Num);
	printf("Valor do ponteiro ptr: %d\n", *Ptr);
	printf("Valor da variável Num: %d\n", Num);
}
