#include <stdio.h>

int prod (int x, int y) {
    return (x * y);
}
int main () {
    int saida;
    saida = prod(12, 7);
    printf("A saida eh: %d \n", saida);
    return (0);
}