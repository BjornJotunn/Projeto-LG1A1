#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int i, im, cped[10], codped;
char formpag[20][20], tpag[10];
float valp[10], vpag;

int main () {
    FILE *Pag;
    i=0;
    Pag = fopen("PAGAMENTOS.DAT" , "r+b");
    while (!feof(Pag)) {
        fread(&codped, sizeof(codped), 1, Pag);
        if (!feof(Pag)) 
            cped[i] = codped;
        fread(&formpag, sizeof(formpag), 1, Pag);
        if (!feof(Pag))
            strcpy(tpag[i], formpag);
        fread(&vpag, sizeof(vpag), 1, Pag);
        if (!feof(Pag))
           valp[i] = vpag;
        i++;
    }
    fclose(Pag);
    im = i;
    for (i=0; i<im; i++)
        printf(" cod [%d] modo [%s] valor [%5.2f]\n", cped[i], formpag[i], valp[i]);
    getch();
    return 0;
}
