#include <stdio.h>
//Exercicio bottons
int main(){
    float vl_unit, desconto, quantidade, vl_tot, vl_desconto, vl_tot_desconto;

    printf("Digite o valor unitario: ");
    scanf("%f", &vl_unit);

    printf("Digite a porcentagem de desconto: ");
    scanf("%f", &desconto);

    printf("Digite a quantidade de bottons que deseja :");
    scanf("%f", &quantidade);

    vl_tot = (vl_unit * quantidade);
    vl_desconto = (vl_unit * quantidade) / 100 * desconto;
    vl_tot_desconto = (vl_tot - vl_desconto);

    if (quantidade >= 100) {

    printf("O valor que ira pagar com desconto eh: R$ %.2f", vl_tot_desconto);

    }else {

    printf("O valor que ira pagar sem desconto eh: R$ %.2f", vl_tot);

    }

}