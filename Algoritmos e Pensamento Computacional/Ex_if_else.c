#include <stdio.h>
//Exercicio if e else
int main(){

    float nota1, nota2, nota3, media;

    printf("Digite sua primeira nota:");
    scanf("%f", &nota1);

    printf("Digite sua segunda nota:");
    scanf("%f", &nota2);

    printf("Digite sua terceira nota:");
    scanf("%f", &nota3);

    media = (nota1 + nota2 + nota3) / 3;

    if (media >= 6)
    {
        printf("voce foi aprovado e sua media eh: %.1f\n", media);
    }else
    {
        printf("voce foi reprovado e sua media eh: %.1f\n", media);
    }

    return 0;
}