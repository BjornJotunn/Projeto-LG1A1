#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int i, im, cped, codped[20];
char cart[20][20], ncart[16];

int main () {
    FILE *Cart;
    i=0;
    Cart = fopen("CARTOES.DAT" , "r+b");
    while (!feof(Cart)) {
        fread(&cped, sizeof(cped), 1, Cart);
        if (!feof(Cart))
            codped[i] = cped;
        fread(&ncart, sizeof(ncart), 1, Cart);
        if (!feof(Cart))
            strcpy(cart[i], ncart);
        i++;
    }
    im = i-1;
    fclose(Cart);
    for (i=0; i<im; i++)
        printf("[%d] [%s]\n", codped[i], cart[i]);
    getch();
    return 0;
}
