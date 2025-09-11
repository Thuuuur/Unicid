#include <stdio.h>

int soma (int a, int b) {
    return a + b;
}
int main () {
    int x = 5, y = 7;
    printf("A soma de %d e %d = %d \n", x, y, soma(x, y));
    return (0);
}