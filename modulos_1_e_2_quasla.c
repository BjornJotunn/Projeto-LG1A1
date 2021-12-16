#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

typedef struct {
	int 	cod;
	char 	descr[20];
	float 	custo;
	//int		line; //flag, recebe 0 ou 1
} registro;

registro 	reg, prod[20], ped[20];
int 		qtd[20], codped[20], fpag[10], ifp;
int 		i, j, iped, ileit, cdped;
float 		vpag[10];

/*void admin (void);
void facapedido (void);
int leitura (void);
int pedido (int ileit);
float total (int im, int iprod);
void notafiscal (int im, float tot, int codped, int ifp);
void cartao (void);
int menupagto (void);
int pagto (float tot, int p);*/

int leitura (void) {
	FILE *Arq;
	printf("\n===================== MENU ========================");
	printf("\n C%cd  Descri%c%co\t\t\t\tValor (R$)", 162, 135, 198);
	printf("\n===================================================\n");

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
			//prod[i].line = reg.line;
			printf("\n%4d  %-30s     R$ %5.2f", reg.cod, reg.descr, reg.custo);
			printf("\n--------------------------------------------------");
			i++;
		}
	}
	printf("\n===================================================");
	fclose(Arq);
	return i;
}

int pedido (int ileit) {
	int p;
	i=0;
	printf("\n\nFa%ca seu pedido!\n", 135);
	
	inicio:
	printf("\nDigite 0 para encerrar o pedido.");
	printf("\nDigite o c%cdigo correspondente ao item que deseja consumir: ", 162);
	fflush(stdin); scanf("%d" , &ped[i].cod);
	if (ped[i].cod > prod[ileit-1].cod) {
		printf("\nOp%c%co inv%clida!\n", 135, 198, 160);
		goto inicio;
	}
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
		if (ped[i].cod > prod[ileit-1].cod) {
			printf("\nOp%c%co inv%clida!", 135, 198, 160);
			i--;
		}
		else {
			p = ped[i].cod-1;
			if (ped[i].cod != 0) {
				printf("Digite a quantidade de %s que deseja: ", prod[p].descr);
				fflush(stdin); scanf("%d" , &qtd[i]);
			}
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
				//ped[i].line = prod[j].line;
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

void notafiscal (int im, float tot, int codped, int ifp) {
	FILE *nota;
	nota = fopen("PAGAMENTOS.txt", "w");
	if (nota == NULL)
		printf("Problemas na abertura do arquivo!");
	else {
		fprintf(nota, "=============================================\n");
		fprintf(nota, "\t\tMickey & Donalds\n");
		fprintf(nota, "=============================================\n");
		fprintf(nota, "\nPedido: %d\n", codped+1);
		fprintf(nota, "\n Cód  Descrição\t\t    Qtd  Valor (R$)");
		for (i=0; i<im; i++) {
			fprintf(nota, "\n%4d  %-20s  %2d x  R$ %5.2f", ped[i].cod, ped[i].descr, qtd[i], ped[i].custo);
			if (qtd[i] > 1)
				fprintf(nota, "\n\t\t\t\t   R$ %5.2f", ped[i].custo*qtd[i]);
		}
		fprintf(nota, "\n\n");
		for (i=0; i<ifp; i++){
			switch(fpag[i]) {
				case 1: fprintf(nota, "\nDinheiro: R$%5.2f", vpag[i]); 			break;
				case 2: fprintf(nota, "\nCartão de Crédito: R$%5.2f", vpag[i]); break;
				case 3: fprintf(nota, "\nCartão de Débito: R$%5.2f", vpag[i]);  break;
				case 4: fprintf(nota, "\nCheque: R$%5.2f", vpag[i]); 			break;
			}
		}
		fprintf(nota, "\n\n\t Total pago: R$ %5.2f", tot);
	}
	fclose(nota);
	system ("notepad PAGAMENTOS.txt");
}

void cartao (int cped) {
	int im;
	char ncart[20], ast = '*';
	FILE *Cart;

	Cart = fopen("CARTOES.DAT", "a+b");
		fwrite(&cped, sizeof(cped), 1, Cart);
	fclose(Cart);

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

int menupagto (void) {
	char opc;
	int fp;
	menu:
	system("color 0B");	
	printf("Escolha uma forma de pagamento:");
	printf("\n1 - Dinheiro");
	printf("\n2 - Cart%co Cr%cdito", 198, 130);
	printf("\n3 - Cart%co D%cbito", 198, 130);
	printf("\n4 - Cheque");
	printf("\n5 - Cancelar");
	printf("\nEscolha: ");
	fflush(stdin); opc = getche();
	switch(opc) {
		default : system("color 4F"); printf("\nOp%c%co inv%clida!", 135, 198, 160); getch(); system("cls"); goto menu; break;
		case '1': system("color 2F"); printf("\n\nVoc%c escolheu Dinheiro!", 136); fp=1; break;
		case '2': system("color DF"); printf("\n\nVoc%c escolheu Cart%co de Cr%cdito!", 136, 198, 130); fp=2; cartao(cdped+1);	break;
		case '3': system("color DF"); printf("\n\nVoc%c escolheu Cart%co de D%cbito!", 136, 198, 130);  fp=3; cartao(cdped+1);	break;
		case '4': system("color 1F"); printf("\n\nVoc%c escolheu Cheque!", 136); fp=4; break;
		case '5': admin(); break;
	}
	return fp;
}

int pagto (float tot) {
	float pg;
	j=0;
	do { //hast
		fpag[j] = menupagto();
		printf("\nTotal: R$ %5.2f\nDigite o valor a ser pago: ", tot);
		fflush(stdin); scanf("%f", &pg);
		if (pg > tot) {
			printf("\nValor digitado %c maior do que o Total a ser pago!", 130);
			getch();
			system("cls");
		}
		if (pg <= tot) {
			tot -= pg;
			vpag[j] = pg;
			j++;
			system("cls");
			if (tot != 0)
				printf("Ainda faltam R$ %5.2f\n", tot);
		}
	} while (tot > 0);
	return j;
}

void admin (void) {
	char opc;
	do { //hast
		system("color 0B");	
		system("cls");
		printf(" ===============================================================\n");
		printf("\t\tBem vindo ao Mickey & Donalds!\n");
		printf(" ===============================================================\n");
		printf("\n     MENU PRINCIPAL\n");
		printf("  1 - Fa%ca seu Pedido\n", 135);
		printf("  2 - Ver Fila\n");
		printf("  0 - Encerrar\n");
		fflush(stdin); opc = getche();
		switch(opc) {
			default : printf("\nOp%c%co inv%clida!", 135, 198, 160); getch(); break;
			case '1': facapedido(); break;
			case '2': break;
			case '0': exit(0);
		}
	} while (!(opc < 48) || !(opc > 50));
}

void facapedido (void) {
	float tt;
	system("cls");
	ileit = leitura();
	iped = pedido(ileit);
	tt = total(iped, ileit);
	getch();
	system("cls");
	ifp = pagto(tt);
	notafiscal(iped, tt, cdped, ifp);
	cdped++;
}
	
int main() {
	cdped=0;
	system("mode con:cols=65 lines=40");
	system("color 0B");	
	system("chcp 850"); //sets code page to universal
	system("cls");
	admin();
	getch();
	return 0;
}
