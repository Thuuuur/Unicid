#include <stdio.h>

int main() {
    float pi = 3.14;
    int raio;
    int area;

    printf("Digite o valor do raio: ");
    scanf("%d", &raio);

    area = pi * raio * raio;

    printf("A area do circulo eh: %d", area);

    return 0;
}