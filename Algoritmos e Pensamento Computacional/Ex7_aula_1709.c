#include <stdio.h>

int main(){

    int x, numero, fat;

    printf("Digite um numero para ver o fatorial: ");
    scanf("%d", &numero);

    fat = 1;

    printf("fatorial do %d : \n", numero);
    for ( x = numero; x >= 1; x--) {
        fat *= x;

    }
    printf("%d! = %d\n", numero, fat);
    return 0;
}