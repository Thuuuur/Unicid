#include <stdio.h>

float retangulo (float comp, float larg) {
    return (comp * larg);
}
int main () {
    float area;
    area = retangulo(12.2, 7.7);
    printf("A saida eh: %.2f \n", area);
    return (0);
}