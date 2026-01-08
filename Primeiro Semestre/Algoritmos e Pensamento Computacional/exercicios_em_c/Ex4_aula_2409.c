#include <stdio.h>

int main() {
    int A [2] [2] [2] = {{{1, 2}, {3, 4}}, {{5, 6}, {7, 8}}};
    int B [2] [2] [2] = {{{8, 7}, {6, 5}}, {{4, 3}, {2, 1}}};
    int C [2] [2] [2];
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++){
            C [i] [j] [k] = A [i] [j] [k] + B [i] [j] [k];
            }
        }
    }
    printf("Resultados da soma dos cubos (2x2x2): \n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
                printf("C[%d][%d][%d] = %d\n", i, j, k, C [i][j][k]);
            }
        }
    }
    return 0;
}