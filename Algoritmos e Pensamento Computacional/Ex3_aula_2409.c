#include <stdio.h>

int main () {
    int A [2] [2] [2] = {
        {{1, 2}, {3, 4}},
        {{5, 6}, {7, 8}}
    };
    printf("Valores do valor tridimensional (2x2x2): \n");
    for (int i = 0; i < 2; i++) {
        for (int j = 0; j < 2; j++) {
            for (int k = 0; k < 2; k++) {
            printf("A [%d] [%d] [%d] = %d \n", i, j, k, A[i] [j] [k]);
            }
        }
    }
    return 0;
}