#include <stdio.h>
//exercicio for
int main(){

    int x, numero;

    printf("Digite um numero para ver a tabuada: ");
    scanf("%d", &numero);

    printf("Tabuada do %d : \n", numero);
    for ( x = 1; x <= 10; x++)

    printf("%d x %d = %d \n", numero, x, numero*x);

    return 0;
}