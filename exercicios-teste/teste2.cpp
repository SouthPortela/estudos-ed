#include <stdio.h>
#include <string.h>

struct Pessoa{
	char Nome[50];
	int Idade;
};

int main(){
	Pessoa user;
	strcpy(user.Nome, "SouthPortela");
	user.Idade = 19;
	Pessoa *Ptr = &user;

	printf("Registro direto: %s - %d\n", user.Nome, user.Idade);
	printf("Registro pelo ponteiro: %s - %d\n", Ptr->Nome, Ptr->Idade);
}
