#include <stdio.h>
#include <string.h>

struct Aluno {
    int matricula;
    char nome[50];
    float media;
};
int main() {
    // Criando uma variável do tipo struct Aluno
    struct Aluno aluno1;
    // Atribuindo valores aos campos da estrutura
    aluno1.matricula = 12345;
    strcpy(aluno1.nome, "Maria Silva");
    aluno1.media = 8.7;
    // Exibindo os dados
    printf("=== Dados do Aluno ===\n");
    printf("Matrícula: %d\n", aluno1.matricula);
    printf("Nome: %s\n", aluno1.nome);
    printf("Média: %.2f\n", aluno1.media);
    // Também é possível criar um array de estruturas
    struct Aluno turma[2] = {
        {11111, "Joao Pereira", 7.5},
        {22222, "Ana Costa", 9.0}
    };
    printf("\n=== Turma ===\n");
    for(int i = 0; i < 2; i++) {
        printf("Aluno %d: %s (Matrícula: %d) - Média: %.2f\n",
        i+1, turma[i].nome, turma[i].matricula, turma[i].media);
    }
    return 0;
}