#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct {
	int 	cod;
	char 	descr[20];
	float 	custo;
} registro;

registro 	reg, prod[20], ped[20];
int 		qtd[10], codped[20];
int 		i, j, iped, ileit, a=0;
float		tt;

void admin (void);
float facapedido (void);
void pagamento (float tt);
int leitura (void);
int pedido (void);
float total (int im, int iprod);
void notafiscal (int im, float tot);
void cartao (void);
void menupagto (void);
void pagto (float tot);

int leitura (void) {
	FILE *Arq;
	printf("\n================ MENU ===============");
	printf("\n C%cd  Descri%c%co           Valor (R$)", 162, 135, 198);
	printf("\n=====================================\n");

	Arq = fopen("PRODUTOS.DAT" , "r+b");
	if (Arq == NULL) {
		printf("\nErro ao abrir PRODUTOS.DAT...");
		getch();
		exit(0);
	}
	i=0;
	while (!feof(Arq)) {
		fread(&reg, sizeof(reg), 1, Arq);
		if (!feof(Arq)) {
			prod[i].cod = reg.cod;
			strcpy(prod[i].descr, reg.descr);
			prod[i].custo = reg.custo;
			printf("\n%4d  %-20s  R$ %5.2f", reg.cod, reg.descr, reg.custo);
			printf("\n-------------------------------------");
			i++;
		}
	}
	printf("\n=====================================");
	fclose(Arq);
	return i;
}

int pedido (void) {
	int p;
	i=0;
	printf("\n\nFa%ca seu pedido!\n", 135);
	printf("\nDigite o c%cdigo correspondente ao item que deseja consumir: ", 162);
	fflush(stdin); scanf("%d" , &ped[i].cod);
	p = ped[i].cod-1;
	if (ped[i].cod != 0) {
		printf("Digite a quantidade de %s que deseja: ", prod[p].descr);
		fflush(stdin); scanf("%d" , &qtd[i]);
	}
	while (ped[i].cod != 0) {
		i++;
		printf("\nDigite 0 para encerrar o pedido.");
		printf("\nMais alguma coisa? ");
		fflush(stdin); scanf("%d" , &ped[i].cod);
		p = ped[i].cod-1;
		if (ped[i].cod != 0) {
			printf("Digite a quantidade de %s que deseja: ", prod[p].descr);
			fflush(stdin); scanf("%d" , &qtd[i]);
		}
	}
	return i;
}

float total (int im, int iprod) {
	float tot=0;
	for (i=0; i<im; i++) {
		for (j=0; j<iprod; j++) {
			if (ped[i].cod == prod[j].cod) {
				strcpy(ped[i].descr, prod[j].descr);
				ped[i].custo = prod[j].custo;
				tot += ped[i].custo*qtd[i];
			}
		}
	}
	for (i=0; i<im; i++) {
		printf("\n%4d  %-20s  %2d x  R$ %5.2f", ped[i].cod, ped[i].descr, qtd[i], ped[i].custo);
		if (qtd[i] > 1)
			printf("\n\t\t\t\t   R$ %5.2f", ped[i].custo*qtd[i]);
	}
	if (tot != 0)
		printf("\n\n\t\tTotal: R$ %5.2f", tot);
	return tot;
}

void notafiscal (int im, float tot) {
	FILE *nota;
	codped[a] = a+1;
	nota = fopen("PAGAMENTOS.txt", "w");
	if (nota == NULL)
		printf("Problemas na abertura do arquivo!");
	else {
		fprintf(nota, "=============================================\n");
		fprintf(nota, "\t\tMickey & Donalds\n");
		fprintf(nota, "=============================================\n");
		fprintf(nota, "\nPedido: %d\n", codped[a++]);
		fprintf(nota, "\n Cód  Descrição\t\t    Qtd  Valor (R$)");
		for (i=0; i<im; i++) {
			fprintf(nota, "\n%4d  %-20s  %2d x  R$ %5.2f", ped[i].cod, ped[i].descr, qtd[i], ped[i].custo);
			if (qtd[i] > 1)
				fprintf(nota, "\n\t\t\t\t   R$ %5.2f", ped[i].custo*qtd[i]);
		}
		fprintf(nota, "\n\n\t\tTotal: R$ %5.2f", tot);
	}
	fclose(nota);
	system ("notepad PAGAMENTOS.txt");
}

void cartao (void) {
	int im;
	char ncart[20], ast = '*';
	FILE *Cart;

	inicio:
	i=0;
	//system("cls");
	printf("\nDigite o n%cmero do cart%co: ", 163, 198);
	fflush(stdin); ncart[i] = getche();
	while (ncart[i] != '\r')
		ncart[++i] = getche();

	im = i;
    printf("\n");
	if (im != 16) {
		printf("Cart%co Inv%clido!", 198, 160);
		goto inicio;
	}
	for (i=0; i<im; i++) {
		Cart = fopen("CARTOES.dat", "a+b");
        if ((i>3) && (i<12)) {
			putchar('*');
           	fwrite(&ast, sizeof(ast), 1, Cart);
        }
        else {
           	printf("%c", ncart[i]);
           	fwrite(&ncart[i], sizeof(ncart[i]), 1, Cart);
        }
		fclose(Cart);
	}
}

void menupagto (void) {
	char opc;
	menu:
	printf("Escolha uma forma de pagamento:");
	printf("\n1 - Dinheiro");
	printf("\n2 - Cart%co Cr%cdito", 198, 130);
	printf("\n3 - Cart%co D%cbito", 198, 130);
	printf("\n4 - Cheque");
	printf("\n5 - Cancelar");
	printf("\nEscolha: ");
	fflush(stdin); opc = getche();
	switch(opc) {
		default : printf("\nOp%c%co inv%clida!", 135, 198, 160); getch(); system("cls"); goto menu; break;
		case '1': printf("\n\nVoc%c escolheu Dinheiro!", 136); break;
		case '2': printf("\n\nVoc%c escolheu Cart%co de Cr%cdito!", 136, 198, 130); cartao();	break;
		case '3': printf("\n\nVoc%c escolheu Cart%co de D%cbito!", 136, 198, 130);  cartao();	break;
		case '4': printf("\n\nVoc%c escolheu Cheque!", 136); break;
		case '5': admin(); break;
	}
}

void pagto (float tot) {
	float pg;
	menupagto();
	do { //hast
		printf("\nTotal: R$ %5.2f\nDigite o valor a ser pago: ", tot);
		fflush(stdin); scanf("%f", &pg);
		if (pg > tot) {
			printf("\nValor digitado %c maior do que o Total a ser pago!", 130);
			getch();
			system("cls");
			menupagto();
		}
		if (pg < tot) {
			tot -= pg;
			system("cls");
			printf("Ainda faltam R$ %5.2f\n", tot);
			menupagto();
		}
	} while (pg != tot);
}

void admin (void) {
	char opc;
	do { //hast
		system("cls");
		printf("   MENU PRINCIPAL\n");
		printf("1 - Fa%ca seu Pedido\n", 135);
		printf("2 - Pagamento\n");
		printf("3 - Ver Fila\n");
		printf("0 - Encerrar\n");
		fflush(stdin); opc = getche();
		switch(opc) {
			default : printf("\nOp%c%co inv%clida!", 135, 198, 160); getch(); break;
			case '1': tt = facapedido(); break;
			case '2': pagamento(tt); break;
			case '3': break;
			case '0': exit(0);
		}
	} while (!(opc < 48) || !(opc > 51));
}

float facapedido (void) {
	float tt;
	system("cls");
	ileit = leitura();
	iped = pedido();
	tt = total(iped, ileit);
	getch();
	return tt;
}

void pagamento (float tt) {
	system("cls");
	pagto(tt);
	notafiscal(iped, tt);
}

int main() {
	system("chcp 850"); //sets code page to universal
	system("cls");
	//codped[a] = a+1;
	admin();
	getch();
	return 0;
}
