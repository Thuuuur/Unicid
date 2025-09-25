#include <stdio.h>

int main () {
    float temp [3] [2] [7];
    float soma;
    float media;
    float tempp;
    int cidade = 1;

    for (int c = 0; c < 3; c++) {
        for (int s = 0; s < 2; s++) {
            for (int d = 0; d < 7; d++) {
                printf("Digite a temperatura de hoje:");
                scanf("%f", &tempp);
                soma = tempp + soma;
            }
        }
        media = soma / 14;
        printf("Media da cidade %d: %.2f\n", cidade, media);
        media = 0;
        cidade++;
    }
    for (int c = 0; c < 3; c++) {
        for (int s = 0; s < 2; s++) {
            for (int d = 0; d < 7; d++) {

            }
        }
        printf("");
    }
}