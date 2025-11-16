#include <stdio.h>
#include <stdlib.h>
//Exercicio base altura perimetro area

int main (int argc, char *argv[])
{
    double base, altura, perimetro, area;

    printf("Entre com a base: ");
    scanf("%lf", &base);

    printf("Entre com a altura: ");
    scanf("%lf", &altura);

    perimetro = 2 * (base + altura);
    area = base * altura;

    printf("\nO perimetro do retangulo eh: %4.llf\n\n", perimetro);
    printf("\nA area do retangulo eh: %4.llf\n\n", area);
    system("PAUSE");
    return 0;
}