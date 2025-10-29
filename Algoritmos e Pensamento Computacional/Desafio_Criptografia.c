#include <stdio.h>
#include <string.h>
#include <ctype.h>

int main() {
    char alfabeto[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
    char alfabetoCifrado[26];
    char texto[100];
    int shift, PA;

    // Entrada do usuário
    printf("Digite seu nome (somente letras): ");
    scanf("%s", texto);

    // Loop para garantir shift válido
    do {
        printf("Digite o shift inicial (0 a 25): ");
        scanf("%d", &shift);
        if (shift < 0 || shift > 25) {
            printf("Shift inválido! Tente novamente.\n");
        }
    } while (shift < 0 || shift > 25);

    // Entrada do termo da progressão aritmética
    printf("Digite o termo da progressao aritmetica (PA): ");
    scanf("%d", &PA);

    // Cria o alfabeto cifrado com P.A.
    int shiftAtual = shift;
    for (int i = 0; i < 26; i++) {
        alfabetoCifrado[i] = alfabeto[(i + shiftAtual) % 26];
        // incrementa shift pela P.A.
        shiftAtual += PA; 
    }

    // Imprime o texto criptografado usando o alfabeto cifrado
    printf("Texto criptografado: ");
    for (int i = 0; i < strlen(texto); i++) {
        char c = toupper(texto[i]);
        if (c >= 'A' && c <= 'Z') {
            int pos = c - 'A';
            printf("%c", alfabetoCifrado[pos]);
        } else {
            // mantém caracteres não-alfabéticos
            printf("%c", c); 
        }
    }
    printf("\n");

    return 0;
}
