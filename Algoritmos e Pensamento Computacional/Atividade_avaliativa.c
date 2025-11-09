#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_PRODUTOS 100
#define ARQUIVO "produtos.txt"

typedef struct {
    int id;
    char nome[50];
    char categoria[30];
    float preco;
    int quantidade;
} Produto;

void toLowerCase(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int compararNomeInsensitive(const char *str1, const char *str2) {
    char temp1[50], temp2[50];
    strcpy(temp1, str1);
    strcpy(temp2, str2);
    toLowerCase(temp1);
    toLowerCase(temp2);
    return strcmp(temp1, temp2);
}

int buscarNome(const char *texto, const char *busca) {
    char textoLower[50], buscaLower[50];
    strcpy(textoLower, texto);
    strcpy(buscaLower, busca);
    toLowerCase(textoLower);
    toLowerCase(buscaLower);
    return strstr(textoLower, buscaLower) != NULL;
}

int obterProximoID() {
    FILE *f = fopen(ARQUIVO, "r");
    int maxID = 0;
    Produto p;
    
    if(f != NULL) {
        while(fscanf(f, "%d;%49[^;];%29[^;];%f;%d\n", &p.id, p.nome, p.categoria, &p.preco, &p.quantidade) == 5) {
            if(p.id > maxID) maxID = p.id;
        }
        fclose(f);
    }
    return maxID + 1;
}

int verificarDuplicata(const char *nome) {
    FILE *f = fopen(ARQUIVO, "r");
    Produto p;
    
    if(f == NULL) return 0;
    
    while(fscanf(f, "%d;%49[^;];%29[^;];%f;%d\n", &p.id, p.nome, p.categoria, &p.preco, &p.quantidade) == 5) {
        if(compararNomeInsensitive(p.nome, nome) == 0) {
            fclose(f);
            return 1;
        }
    }
    fclose(f);
    return 0;
}

void criarArquivo() {
    FILE *f = fopen(ARQUIVO, "r");
    if(f == NULL) {
        f = fopen(ARQUIVO, "w");
        if(f != NULL) {
            printf("Arquivo criado com sucesso!\n");
            fclose(f);
        }
    } else {
        printf("Arquivo ja existe!\n");
        fclose(f);
    }
}

void inserirProduto() {
    Produto p;
    FILE *f;
    
    printf("\n=== INSERIR PRODUTO ===\n");
    printf("Nome: ");
    scanf(" %49[^\n]", p.nome);
    
    if(verificarDuplicata(p.nome)) {
        printf("ERRO: Produto com este nome ja existe!\n");
        return;
    }
    
    p.id = obterProximoID();
    
    printf("Categoria: ");
    scanf(" %29[^\n]", p.categoria);
    printf("Preco: ");
    scanf("%f", &p.preco);
    printf("Quantidade: ");
    scanf("%d", &p.quantidade);
    
    f = fopen(ARQUIVO, "a");
    if(f != NULL) {
        fprintf(f, "%d;%s;%s;%.2f;%d\n", p.id, p.nome, p.categoria, p.preco, p.quantidade);
        fclose(f);
        printf("Produto inserido com sucesso! ID: %d\n", p.id);
    } else {
        printf("Erro ao abrir arquivo!\n");
    }
}

int carregarProdutos(Produto lista[]) {
    FILE *f = fopen(ARQUIVO, "r");
    int count = 0;
    
    if(f == NULL) return 0;
    
    while(fscanf(f, "%d;%49[^;];%29[^;];%f;%d\n", &lista[count].id, lista[count].nome, 
                 lista[count].categoria, &lista[count].preco, &lista[count].quantidade) == 5) {
        count++;
        if(count >= MAX_PRODUTOS) break;
    }
    fclose(f);
    return count;
}

void exibirTabela(Produto lista[], int total) {
    printf("\n+-----+--------------------------------------------------+------------------------------+----------+----------+\n");
    printf("| %-3s | %-48s | %-28s | %-8s | %-8s |\n", "ID", "Nome", "Categoria", "Preco", "Qtd");
    printf("+-----+--------------------------------------------------+------------------------------+----------+----------+\n");
    
    for(int i = 0; i < total; i++) {
        printf("| %-3d | %-48s | %-28s | %8.2f | %8d |\n", 
               lista[i].id, lista[i].nome, lista[i].categoria, lista[i].preco, lista[i].quantidade);
    }
    printf("+-----+--------------------------------------------------+------------------------------+----------+----------+\n");
}

void listarProdutos() {
    Produto lista[MAX_PRODUTOS];
    int total = carregarProdutos(lista);
    
    if(total == 0) {
        printf("Nenhum produto cadastrado!\n");
        return;
    }
    
    printf("\n=== LISTA DE PRODUTOS ===\n");
    exibirTabela(lista, total);
}

void bubbleSortNomeAZ(Produto lista[], int total) {
    for(int i = 0; i < total - 1; i++) {
        for(int j = 0; j < total - i - 1; j++) {
            if(compararNomeInsensitive(lista[j].nome, lista[j+1].nome) > 0) {
                Produto temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

void bubbleSortNomeZA(Produto lista[], int total) {
    for(int i = 0; i < total - 1; i++) {
        for(int j = 0; j < total - i - 1; j++) {
            if(compararNomeInsensitive(lista[j].nome, lista[j+1].nome) < 0) {
                Produto temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

void bubbleSortPrecoMenorMaior(Produto lista[], int total) {
    for(int i = 0; i < total - 1; i++) {
        for(int j = 0; j < total - i - 1; j++) {
            if(lista[j].preco > lista[j+1].preco) {
                Produto temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

void bubbleSortPrecoMaiorMenor(Produto lista[], int total) {
    for(int i = 0; i < total - 1; i++) {
        for(int j = 0; j < total - i - 1; j++) {
            if(lista[j].preco < lista[j+1].preco) {
                Produto temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

void ordenarProdutos() {
    Produto lista[MAX_PRODUTOS];
    int total = carregarProdutos(lista);
    int opcao;
    
    if(total == 0) {
        printf("Nenhum produto cadastrado!\n");
        return;
    }
    
    printf("\n=== ORDENAR PRODUTOS ===\n");
    printf("1. Nome (A-Z)\n");
    printf("2. Nome (Z-A)\n");
    printf("3. Preco (Menor -> Maior)\n");
    printf("4. Preco (Maior -> Menor)\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    
    switch(opcao) {
        case 1:
            bubbleSortNomeAZ(lista, total);
            printf("\n=== PRODUTOS ORDENADOS POR NOME (A-Z) ===\n");
            break;
        case 2:
            bubbleSortNomeZA(lista, total);
            printf("\n=== PRODUTOS ORDENADOS POR NOME (Z-A) ===\n");
            break;
        case 3:
            bubbleSortPrecoMenorMaior(lista, total);
            printf("\n=== PRODUTOS ORDENADOS POR PRECO (MENOR -> MAIOR) ===\n");
            break;
        case 4:
            bubbleSortPrecoMaiorMenor(lista, total);
            printf("\n=== PRODUTOS ORDENADOS POR PRECO (MAIOR -> MENOR) ===\n");
            break;
        default:
            printf("Opcao invalida!\n");
            return;
    }
    
    exibirTabela(lista, total);
}

void buscarPorNome() {
    Produto lista[MAX_PRODUTOS];
    int total = carregarProdutos(lista);
    char busca[50];
    int encontrados = 0;
    
    if(total == 0) {
        printf("Nenhum produto cadastrado!\n");
        return;
    }
    
    printf("\n=== BUSCAR POR NOME ===\n");
    printf("Digite o nome: ");
    scanf(" %49[^\n]", busca);
    
    printf("\n=== RESULTADOS DA BUSCA ===\n");
    
    for(int i = 0; i < total; i++) {
        if(buscarNome(lista[i].nome, busca)) {
            if(encontrados == 0) {
                printf("+-----+--------------------------------------------------+------------------------------+----------+----------+\n");
                printf("| %-3s | %-48s | %-28s | %-8s | %-8s |\n", "ID", "Nome", "Categoria", "Preco", "Qtd");
                printf("+-----+--------------------------------------------------+------------------------------+----------+----------+\n");
            }
            printf("| %-3d | %-48s | %-28s | %8.2f | %8d |\n", 
                   lista[i].id, lista[i].nome, lista[i].categoria, lista[i].preco, lista[i].quantidade);
            encontrados++;
        }
    }
    
    if(encontrados > 0) {
        printf("+-----+--------------------------------------------------+------------------------------+----------+----------+\n");
        printf("Total encontrado: %d\n", encontrados);
    } else {
        printf("Nenhum produto encontrado!\n");
    }
}

void buscarPorCategoria() {
    Produto lista[MAX_PRODUTOS];
    int total = carregarProdutos(lista);
    char busca[30];
    int encontrados = 0;
    
    if(total == 0) {
        printf("Nenhum produto cadastrado!\n");
        return;
    }
    
    printf("\n=== BUSCAR POR CATEGORIA ===\n");
    printf("Digite a categoria: ");
    scanf(" %29[^\n]", busca);
    
    printf("\n=== RESULTADOS DA BUSCA ===\n");
    
    for(int i = 0; i < total; i++) {
        if(buscarNome(lista[i].categoria, busca)) {
            if(encontrados == 0) {
                printf("+-----+--------------------------------------------------+------------------------------+----------+----------+\n");
                printf("| %-3s | %-48s | %-28s | %-8s | %-8s |\n", "ID", "Nome", "Categoria", "Preco", "Qtd");
                printf("+-----+--------------------------------------------------+------------------------------+----------+----------+\n");
            }
            printf("| %-3d | %-48s | %-28s | %8.2f | %8d |\n", 
                   lista[i].id, lista[i].nome, lista[i].categoria, lista[i].preco, lista[i].quantidade);
            encontrados++;
        }
    }
    
    if(encontrados > 0) {
        printf("+-----+--------------------------------------------------+------------------------------+----------+----------+\n");
        printf("Total encontrado: %d\n", encontrados);
    } else {
        printf("Nenhum produto encontrado!\n");
    }
}

void alterarProduto() {
    Produto p;
    int id, encontrado = 0;
    FILE *f, *temp;
    
    printf("\n=== ALTERAR PRODUTO ===\n");
    printf("Digite o ID do produto: ");
    scanf("%d", &id);
    
    f = fopen(ARQUIVO, "r");
    temp = fopen("temp.txt", "w");
    
    if(f == NULL || temp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        if(f) fclose(f);
        if(temp) fclose(temp);
        return;
    }
    
    while(fscanf(f, "%d;%49[^;];%29[^;];%f;%d\n", &p.id, p.nome, p.categoria, &p.preco, &p.quantidade) == 5) {
        if(p.id == id) {
            encontrado = 1;
            printf("Produto encontrado: %s\n", p.nome);
            printf("Novo nome (ou Enter para manter): ");
            char buffer[50];
            scanf(" %49[^\n]", buffer);
            if(strlen(buffer) > 0) strcpy(p.nome, buffer);
            
            printf("Nova categoria (ou Enter para manter): ");
            scanf(" %29[^\n]", buffer);
            if(strlen(buffer) > 0) strcpy(p.categoria, buffer);
            
            printf("Novo preco (ou 0 para manter): ");
            float novoPreco;
            scanf("%f", &novoPreco);
            if(novoPreco > 0) p.preco = novoPreco;
            
            printf("Nova quantidade (ou -1 para manter): ");
            int novaQtd;
            scanf("%d", &novaQtd);
            if(novaQtd >= 0) p.quantidade = novaQtd;
        }
        fprintf(temp, "%d;%s;%s;%.2f;%d\n", p.id, p.nome, p.categoria, p.preco, p.quantidade);
    }
    
    fclose(f);
    fclose(temp);
    
    if(encontrado) {
        remove(ARQUIVO);
        rename("temp.txt", ARQUIVO);
        printf("Produto alterado com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Produto nao encontrado!\n");
    }
}

void excluirProduto() {
    Produto p;
    int id, encontrado = 0;
    FILE *f, *temp;
    
    printf("\n=== EXCLUIR PRODUTO ===\n");
    printf("Digite o ID do produto: ");
    scanf("%d", &id);
    
    f = fopen(ARQUIVO, "r");
    temp = fopen("temp.txt", "w");
    
    if(f == NULL || temp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        if(f) fclose(f);
        if(temp) fclose(temp);
        return;
    }
    
    while(fscanf(f, "%d;%49[^;];%29[^;];%f;%d\n", &p.id, p.nome, p.categoria, &p.preco, &p.quantidade) == 5) {
        if(p.id == id) {
            encontrado = 1;
            printf("Produto excluido: %s\n", p.nome);
        } else {
            fprintf(temp, "%d;%s;%s;%.2f;%d\n", p.id, p.nome, p.categoria, p.preco, p.quantidade);
        }
    }
    
    fclose(f);
    fclose(temp);
    
    if(encontrado) {
        remove(ARQUIVO);
        rename("temp.txt", ARQUIVO);
        printf("Produto excluido com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Produto nao encontrado!\n");
    }
}

void exportarCSV() {
    Produto p;
    FILE *f, *csv;
    
    f = fopen(ARQUIVO, "r");
    csv = fopen("produtos.csv", "w");
    
    if(f == NULL || csv == NULL) {
        printf("Erro ao abrir arquivo!\n");
        if(f) fclose(f);
        if(csv) fclose(csv);
        return;
    }
    
    fprintf(csv, "ID,Nome,Categoria,Preco,Quantidade\n");
    
    while(fscanf(f, "%d;%49[^;];%29[^;];%f;%d\n", &p.id, p.nome, p.categoria, &p.preco, &p.quantidade) == 5) {
        fprintf(csv, "%d,%s,%s,%.2f,%d\n", p.id, p.nome, p.categoria, p.preco, p.quantidade);
    }
    
    fclose(f);
    fclose(csv);
    printf("Dados exportados para produtos.csv com sucesso!\n");
}

int main() {
    int opcao;
    
    do {
        printf("\n========== SISTEMA DE CADASTRO DE PRODUTOS ==========\n");
        printf("1. Criar arquivo\n");
        printf("2. Inserir produto\n");
        printf("3. Listar produtos\n");
        printf("4. Alterar produto\n");
        printf("5. Excluir produto\n");
        printf("6. Buscar por nome\n");
        printf("7. Buscar por categoria\n");
        printf("8. Ordenar produtos\n");
        printf("9. Exportar para CSV\n");
        printf("0. Sair\n");
        printf("=====================================================\n");
        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 1: criarArquivo(); break;
            case 2: inserirProduto(); break;
            case 3: listarProdutos(); break;
            case 4: alterarProduto(); break;
            case 5: excluirProduto(); break;
            case 6: buscarPorNome(); break;
            case 7: buscarPorCategoria(); break;
            case 8: ordenarProdutos(); break;
            case 9: exportarCSV(); break;
            case 0: printf("Encerrando...\n"); break;
            default: printf("Opcao invalida!\n");
        }
    } while(opcao != 0);
    
    return 0;
}