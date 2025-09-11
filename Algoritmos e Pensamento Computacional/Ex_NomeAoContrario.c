#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <string.h>

int main() {
    int x, tam;
    char nome[30];

    printf("Digite uma palavra: ");
    gets(nome);

    tam = strlen(nome);
    printf("\n A palavra de tras pra frente eh: ");

    for ( x = tam - 1; x >= 0; x--)

    printf("%c", nome[x]);
    printf("\n\n");

    system("PAUSE");
    return 0;
}