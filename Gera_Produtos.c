#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct {
	int 	cod;
	char 	descr[30];
	float 	custo;
	int		line;
} registro;

registro 	reg;
FILE 		*Arq;
char 		opc;

int main() {
	system("chcp 860");
	printf("\b");
	do { //hast
		printf("\nDigite o c%cdigo: ", 162);
		fflush(stdin); scanf("%d" , &reg.cod);
		printf("\nDigite a descri%c%co: ", 135, 132);
		fflush(stdin); gets(reg.descr);
		printf("\nDigite o valor: ");
		fflush(stdin); scanf("%f" , &reg.custo);
		printf("\nVai para fila? [0 = n%co] [1 = sim] ", 132);
		fflush(stdin); scanf("%d" , &reg.line);
	
		Arq = fopen("PRODUTOS.DAT" , "a+b");
		if (Arq == NULL) {
			printf("\nErro ao abrir PRODUTOS.DAT...");
			getch();
			exit(0);
		}
		fwrite(&reg, sizeof(reg), 1, Arq);
		fclose(Arq);
	
		printf("\nCadastra outro? [n/N = n%co]: ", 132);
		fflush(stdin); opc = getche();
	}
	while (opc != 'n' && opc != 'N');
	
	getch();
	return 0;
}
