#include <stdio.h>
#include <string.h>

struct Aluno {
    char nome[50];
    int matricula;
    float notas[3];
    float media;
};

int main() {
    int N, i, j;
    int aprovados = 0, reprovados = 0;
    int idxMaior = 0, idxMenor = 0;

    printf("Digite a quantidade de alunos: ");
    scanf("%d", &N);

    struct Aluno alunos[N];

    // Cadastro
    for (i = 0; i < N; i++) {
        printf("\nAluno %d:\n", i + 1);
        printf("Nome: ");
        scanf(" %[^\n]", alunos[i].nome); // lê string com espaços
        printf("Matricula: ");
        scanf("%d", &alunos[i].matricula);
        alunos[i].media = 0;

        for (j = 0; j < 3; j++) {
            printf("Nota %d: ", j + 1);
            scanf("%f", &alunos[i].notas[j]);
            alunos[i].media += alunos[i].notas[j];
        }
        alunos[i].media /= 3.0;
    }
    // Encontrar maior e menor média
    for (i = 1; i < N; i++) {
        if (alunos[i].media > alunos[idxMaior].media)
            idxMaior = i;
        if (alunos[i].media < alunos[idxMenor].media)
            idxMenor = i;
    }
    // Relatório final
    printf("\n--- Relatorio Final ---\n");
    for (i = 0; i < N; i++) {
        printf("%s (Matricula: %d) - Media: %.2f - %s\n",
        alunos[i].nome, alunos[i].matricula,
        alunos[i].media,
        (alunos[i].media >= 7) ? "Aprovado" : "Reprovado");
        if (alunos[i].media >= 7) aprovados++;
        else reprovados++;
    }
    printf("\nMaior media: %s (%.2f)\n", alunos[idxMaior].nome,
    alunos[idxMaior].media);
    printf("Menor media: %s (%.2f)\n", alunos[idxMenor].nome,
    alunos[idxMenor].media);
    printf("Total aprovados: %d\n", aprovados);
    printf("Total reprovados: %d\n", reprovados);
    return 0;
}