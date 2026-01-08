#include <stdio.h>
#include <math.h>
#include <stdbool.h>

// ----------- PROGRESSÃO ARITMÉTICA -----------
void progressaoAritmetica(int a1, int r, int n) {
    printf("\nProgressão Aritmética (PA):\n");
    for (int i = 0; i < n; i++) {
        int termo = a1 + i * r;
        printf("%d ", termo);
    }
    printf("\n");
}

// ----------- PROGRESSÃO GEOMÉTRICA -----------
void progressaoGeometrica(int a1, int q, int n) {
    printf("\nProgressão Geométrica (PG):\n");
    for (int i = 0; i < n; i++) {
        int termo = a1 * pow(q, i);
        printf("%d ", termo);
    }
    printf("\n");
}

// ----------- NÚMEROS PRIMOS -----------
bool ehPrimo(int num) {
    if (num < 2) return false;
    for (int i = 2; i <= sqrt(num); i++) {
        if (num % i == 0) return false;
    }
    return true;
}

void numerosPrimos(int limite) {
    printf("\nNúmeros Primos até %d:\n", limite);
    for (int i = 2; i <= limite; i++) {
        if (ehPrimo(i)) printf("%d ", i);
    }
    printf("\n");
}

// ----------- SÉRIE DE FIBONACCI -----------
void serieFibonacci(int n) {
    printf("\nSérie de Fibonacci:\n");
    int a = 1, b = 1, c;
    printf("%d %d ", a, b);
    for (int i = 3; i <= n; i++) {
        c = a + b;
        printf("%d ", c);
        a = b;
        b = c;
    }
    printf("\n");
}

// ----------- INCREMENTO EM PROGRESSÃO -----------
void incrementoLinear(int inicio, int passo, int n) {
    printf("\nIncremento Linear:\n");
    for (int i = 0; i < n; i++) {
        int valor = inicio + i * passo;
        printf("%d ", valor);
    }
    printf("\n");
}

void incrementoGeometrico(int inicio, int razao, int n) {
    printf("\nIncremento Geométrico:\n");
    for (int i = 0; i < n; i++) {
        int valor = inicio * pow(razao, i);
        printf("%d ", valor);
    }
    printf("\n");
}

// ----------- PROGRAMA PRINCIPAL COM MENU -----------
int main() {
    int opcao;
    printf("=== MENU DE FUNÇÕES MATEMÁTICAS ===\n");
    printf("1 - Progressão Aritmética (PA)\n");
    printf("2 - Progressão Geométrica (PG)\n");
    printf("3 - Números Primos\n");
    printf("4 - Série de Fibonacci\n");
    printf("5 - Incremento em Progressão\n");
    printf("Escolha uma opção (1 a 5): ");
    scanf("%d", &opcao);

    switch (opcao) {
        case 1: {
            int a1, r, n;
            printf("Digite o primeiro termo (a1): ");
            scanf("%d", &a1);
            printf("Digite a razão (r): ");
            scanf("%d", &r);
            printf("Digite o número de termos (n): ");
            scanf("%d", &n);
            progressaoAritmetica(a1, r, n);
            break;
        }
        case 2: {
            int a1, q, n;
            printf("Digite o primeiro termo (a1): ");
            scanf("%d", &a1);
            printf("Digite a razão (q): ");
            scanf("%d", &q);
            printf("Digite o número de termos (n): ");
            scanf("%d", &n);
            progressaoGeometrica(a1, q, n);
            break;
        }
        case 3: {
            int limite;
            printf("Listar números primos até: ");
            scanf("%d", &limite);
            numerosPrimos(limite);
            break;
        }
        case 4: {
            int n;
            printf("Digite quantos termos da série de Fibonacci deseja: ");
            scanf("%d", &n);
            serieFibonacci(n);
            break;
        }
        case 5: {
            int tipo, inicio, valor, n;
            printf("Escolha o tipo de incremento:\n1 - Linear\n2 - Geométrico\n");
            scanf("%d", &tipo);
            printf("Digite o valor inicial: ");
            scanf("%d", &inicio);
            printf("Digite o passo/razão: ");
            scanf("%d", &valor);
            printf("Digite o número de termos: ");
            scanf("%d", &n);
            if (tipo == 1)
                incrementoLinear(inicio, valor, n);
            else
                incrementoGeometrico(inicio, valor, n);
            break;
        }
        default:
            printf("Opção inválida!\n");
            break;
    }

    printf("\n=== Fim do programa ===\n");
    return 0;
}
