#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// Define o número máximo de produtos que podem ser carregados na memória
#define MAX_PRODUTOS 100
// Define o nome do arquivo onde os dados serão armazenados
#define ARQUIVO "produtos.txt"

// Estrutura que representa um produto com todos seus atributos
typedef struct {
    int id;                  // Identificador único do produto
    char nome[50];          // Nome do produto (até 49 caracteres + \0)
    char categoria[30];     // Categoria do produto (até 29 caracteres + \0)
    float preco;            // Preço do produto
    int quantidade;         // Quantidade em estoque
    char fornecedor[50];    // Nome do fornecedor (até 49 caracteres + \0)
} Produto;

// Função auxiliar: converte uma string para letras minúsculas
// Parâmetro: str - string a ser convertida (modificada in-place)
void toLowerCase(char *str) {
    for(int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);  // Converte cada caractere para minúscula
    }
}

// Compara duas strings ignorando maiúsculas/minúsculas
// Retorna: 0 se iguais, <0 se str1 < str2, >0 se str1 > str2
int compararNomeInsensitive(const char *str1, const char *str2) {
    char temp1[50], temp2[50];
    strcpy(temp1, str1);           // Copia para não modificar as originais
    strcpy(temp2, str2);
    toLowerCase(temp1);            // Converte ambas para minúsculas
    toLowerCase(temp2);
    return strcmp(temp1, temp2);   // Compara as versões em minúsculas
}

// Verifica se uma substring existe dentro de um texto (case-insensitive)
// Retorna: 1 se encontrou, 0 se não encontrou
int buscarNome(const char *texto, const char *busca) {
    char textoLower[50], buscaLower[50];
    strcpy(textoLower, texto);
    strcpy(buscaLower, busca);
    toLowerCase(textoLower);       // Converte ambos para minúsculas
    toLowerCase(buscaLower);
    return strstr(textoLower, buscaLower) != NULL;  // strstr retorna NULL se não encontrar
}

// Lê o arquivo e retorna o próximo ID disponível (maior ID + 1)
// Isso garante IDs únicos e sequenciais
int obterProximoID() {
    FILE *f = fopen(ARQUIVO, "r");
    int maxID = 0;
    Produto p;
    
    if(f != NULL) {
        // Lê cada linha do arquivo procurando o maior ID
        while(fscanf(f, "%d;%49[^;];%29[^;];%f;%d;%49[^\n]\n", 
                     &p.id, p.nome, p.categoria, &p.preco, &p.quantidade, p.fornecedor) == 6) {
            if(p.id > maxID) maxID = p.id;  // Atualiza o maior ID encontrado
        }
        fclose(f);
    }
    return maxID + 1;  // Retorna o próximo ID disponível
}

// Verifica se já existe um produto com o mesmo nome no arquivo
// Retorna: 1 se existe duplicata, 0 se não existe
int verificarDuplicata(const char *nome) {
    FILE *f = fopen(ARQUIVO, "r");
    Produto p;
    
    if(f == NULL) return 0;  // Se arquivo não existe, não há duplicatas
    
    // Percorre todos os produtos buscando nome igual (case-insensitive)
    while(fscanf(f, "%d;%49[^;];%29[^;];%f;%d;%49[^\n]\n", 
                 &p.id, p.nome, p.categoria, &p.preco, &p.quantidade, p.fornecedor) == 6) {
        if(compararNomeInsensitive(p.nome, nome) == 0) {
            fclose(f);
            return 1;  // Encontrou duplicata
        }
    }
    fclose(f);
    return 0;  // Não encontrou duplicata
}

// Cria o arquivo de produtos se ele ainda não existir
void criarArquivo() {
    FILE *f = fopen(ARQUIVO, "r");  // Tenta abrir para leitura
    if(f == NULL) {
        f = fopen(ARQUIVO, "w");    // Se não existe, cria o arquivo
        if(f != NULL) {
            printf("Arquivo criado com sucesso!\n");
            fclose(f);
        }
    } else {
        printf("Arquivo ja existe!\n");
        fclose(f);
    }
}

// Função para inserir um novo produto no sistema
void inserirProduto() {
    Produto p;
    FILE *f;
    
    printf("\n=== INSERIR PRODUTO ===\n");
    printf("Nome: ");
    scanf(" %49[^\n]", p.nome);  // Lê até 49 caracteres ou até encontrar \n
    
    // Verifica se já existe produto com este nome
    if(verificarDuplicata(p.nome)) {
        printf("ERRO: Produto com este nome ja existe!\n");
        return;
    }
    
    // Gera automaticamente o próximo ID disponível
    p.id = obterProximoID();
    
    // Coleta os demais dados do produto
    printf("Categoria: ");
    scanf(" %29[^\n]", p.categoria);
    printf("Preco: ");
    scanf("%f", &p.preco);
    printf("Quantidade: ");
    scanf("%d", &p.quantidade);
    printf("Fornecedor: ");
    scanf(" %49[^\n]", p.fornecedor);
    
    // Abre o arquivo em modo append (adiciona no final)
    f = fopen(ARQUIVO, "a");
    if(f != NULL) {
        // Grava o produto no formato: id;nome;categoria;preco;quantidade;fornecedor
        fprintf(f, "%d;%s;%s;%.2f;%d;%s\n", p.id, p.nome, p.categoria, p.preco, p.quantidade, p.fornecedor);
        fclose(f);
        printf("Produto inserido com sucesso! ID: %d\n", p.id);
    } else {
        printf("Erro ao abrir arquivo!\n");
    }
}

// Carrega todos os produtos do arquivo para um array em memória
// Retorna: número de produtos carregados
int carregarProdutos(Produto lista[]) {
    FILE *f = fopen(ARQUIVO, "r");
    int count = 0;
    
    if(f == NULL) return 0;  // Arquivo não existe ou erro ao abrir
    
    // Lê cada linha do arquivo e armazena no array
    while(fscanf(f, "%d;%49[^;];%29[^;];%f;%d;%49[^\n]\n", 
                 &lista[count].id, lista[count].nome, lista[count].categoria, 
                 &lista[count].preco, &lista[count].quantidade, lista[count].fornecedor) == 6) {
        count++;
        if(count >= MAX_PRODUTOS) break;  // Evita overflow do array
    }
    fclose(f);
    return count;
}

// Exibe os produtos em formato de tabela organizada
void exibirTabela(Produto lista[], int total) {
    // Desenha a linha superior da tabela
    printf("\n+-----+--------------------------------------------------+------------------------------+----------+----------+--------------------------------------------------+\n");
    // Exibe os cabeçalhos das colunas
    printf("| %-3s | %-48s | %-28s | %-8s | %-8s | %-48s |\n", 
           "ID", "Nome", "Categoria", "Preco", "Qtd", "Fornecedor");
    printf("+-----+--------------------------------------------------+------------------------------+----------+----------+--------------------------------------------------+\n");
    
    // Exibe cada produto em uma linha da tabela
    for(int i = 0; i < total; i++) {
        printf("| %-3d | %-48s | %-28s | %8.2f | %8d | %-48s |\n", 
               lista[i].id, lista[i].nome, lista[i].categoria, 
               lista[i].preco, lista[i].quantidade, lista[i].fornecedor);
    }
    // Desenha a linha inferior da tabela
    printf("+-----+--------------------------------------------------+------------------------------+----------+----------+--------------------------------------------------+\n");
}

// Lista todos os produtos cadastrados
void listarProdutos() {
    Produto lista[MAX_PRODUTOS];
    int total = carregarProdutos(lista);  // Carrega produtos do arquivo
    
    if(total == 0) {
        printf("Nenhum produto cadastrado!\n");
        return;
    }
    
    printf("\n=== LISTA DE PRODUTOS ===\n");
    exibirTabela(lista, total);  // Exibe em formato de tabela
}

// Algoritmo Bubble Sort para ordenar por nome de A-Z
void bubbleSortNomeAZ(Produto lista[], int total) {
    for(int i = 0; i < total - 1; i++) {
        for(int j = 0; j < total - i - 1; j++) {
            // Compara nomes ignorando maiúsculas/minúsculas
            if(compararNomeInsensitive(lista[j].nome, lista[j+1].nome) > 0) {
                // Troca os produtos de posição
                Produto temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

// Algoritmo Bubble Sort para ordenar por nome de Z-A
void bubbleSortNomeZA(Produto lista[], int total) {
    for(int i = 0; i < total - 1; i++) {
        for(int j = 0; j < total - i - 1; j++) {
            // Inverte a comparação para ordem decrescente
            if(compararNomeInsensitive(lista[j].nome, lista[j+1].nome) < 0) {
                Produto temp = lista[j];
                lista[j] = lista[j+1];
                lista[j+1] = temp;
            }
        }
    }
}

// Algoritmo Bubble Sort para ordenar por preço (menor para maior)
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

// Algoritmo Bubble Sort para ordenar por preço (maior para menor)
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

// Menu para ordenar produtos por diferentes critérios
void ordenarProdutos() {
    Produto lista[MAX_PRODUTOS];
    int total = carregarProdutos(lista);
    int opcao;
    
    if(total == 0) {
        printf("Nenhum produto cadastrado!\n");
        return;
    }
    
    // Exibe menu de opções de ordenação
    printf("\n=== ORDENAR PRODUTOS ===\n");
    printf("1. Nome (A-Z)\n");
    printf("2. Nome (Z-A)\n");
    printf("3. Preco (Menor -> Maior)\n");
    printf("4. Preco (Maior -> Menor)\n");
    printf("Escolha: ");
    scanf("%d", &opcao);
    
    // Executa a ordenação escolhida
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
    
    exibirTabela(lista, total);  // Exibe a lista ordenada
}

// Busca produtos pelo nome (busca parcial, case-insensitive)
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
    
    // Percorre todos os produtos buscando correspondências
    for(int i = 0; i < total; i++) {
        if(buscarNome(lista[i].nome, busca)) {
            // Exibe cabeçalho da tabela apenas no primeiro resultado
            if(encontrados == 0) {
                printf("+-----+--------------------------------------------------+------------------------------+----------+----------+--------------------------------------------------+\n");
                printf("| %-3s | %-48s | %-28s | %-8s | %-8s | %-48s |\n", 
                       "ID", "Nome", "Categoria", "Preco", "Qtd", "Fornecedor");
                printf("+-----+--------------------------------------------------+------------------------------+----------+----------+--------------------------------------------------+\n");
            }
            printf("| %-3d | %-48s | %-28s | %8.2f | %8d | %-48s |\n", 
                   lista[i].id, lista[i].nome, lista[i].categoria, 
                   lista[i].preco, lista[i].quantidade, lista[i].fornecedor);
            encontrados++;
        }
    }
    
    // Exibe resultado da busca
    if(encontrados > 0) {
        printf("+-----+--------------------------------------------------+------------------------------+----------+----------+--------------------------------------------------+\n");
        printf("Total encontrado: %d\n", encontrados);
    } else {
        printf("Nenhum produto encontrado!\n");
    }
}

// Busca produtos pela categoria (busca parcial, case-insensitive)
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
    
    // Percorre todos os produtos buscando correspondências na categoria
    for(int i = 0; i < total; i++) {
        if(buscarNome(lista[i].categoria, busca)) {
            if(encontrados == 0) {
                printf("+-----+--------------------------------------------------+------------------------------+----------+----------+--------------------------------------------------+\n");
                printf("| %-3s | %-48s | %-28s | %-8s | %-8s | %-48s |\n", 
                       "ID", "Nome", "Categoria", "Preco", "Qtd", "Fornecedor");
                printf("+-----+--------------------------------------------------+------------------------------+----------+----------+--------------------------------------------------+\n");
            }
            printf("| %-3d | %-48s | %-28s | %8.2f | %8d | %-48s |\n", 
                   lista[i].id, lista[i].nome, lista[i].categoria, 
                   lista[i].preco, lista[i].quantidade, lista[i].fornecedor);
            encontrados++;
        }
    }
    
    if(encontrados > 0) {
        printf("+-----+--------------------------------------------------+------------------------------+----------+----------+--------------------------------------------------+\n");
        printf("Total encontrado: %d\n", encontrados);
    } else {
        printf("Nenhum produto encontrado!\n");
    }
}

// Altera os dados de um produto existente
void alterarProduto() {
    Produto p;
    int id, encontrado = 0;
    FILE *f, *temp;
    
    printf("\n=== ALTERAR PRODUTO ===\n");
    printf("Digite o ID do produto: ");
    scanf("%d", &id);
    
    // Abre arquivo original para leitura e temporário para escrita
    f = fopen(ARQUIVO, "r");
    temp = fopen("temp.txt", "w");
    
    if(f == NULL || temp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        if(f) fclose(f);
        if(temp) fclose(temp);
        return;
    }
    
    // Lê cada produto do arquivo
    while(fscanf(f, "%d;%49[^;];%29[^;];%f;%d;%49[^\n]\n", 
                 &p.id, p.nome, p.categoria, &p.preco, &p.quantidade, p.fornecedor) == 6) {
        if(p.id == id) {
            encontrado = 1;
            printf("Produto encontrado: %s\n", p.nome);
            
            // Permite alterar cada campo (se deixar vazio, mantém o valor atual)
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
            
            printf("Novo fornecedor (ou Enter para manter): ");
            scanf(" %49[^\n]", buffer);
            if(strlen(buffer) > 0) strcpy(p.fornecedor, buffer);
        }
        // Grava o produto (alterado ou não) no arquivo temporário
        fprintf(temp, "%d;%s;%s;%.2f;%d;%s\n", p.id, p.nome, p.categoria, p.preco, p.quantidade, p.fornecedor);
    }
    
    fclose(f);
    fclose(temp);
    
    if(encontrado) {
        // Substitui o arquivo original pelo temporário
        remove(ARQUIVO);
        rename("temp.txt", ARQUIVO);
        printf("Produto alterado com sucesso!\n");
    } else {
        remove("temp.txt");  // Remove temporário se não encontrou o produto
        printf("Produto nao encontrado!\n");
    }
}

// Exclui um produto do sistema
void excluirProduto() {
    Produto p;
    int id, encontrado = 0;
    FILE *f, *temp;
    
    printf("\n=== EXCLUIR PRODUTO ===\n");
    printf("Digite o ID do produto: ");
    scanf("%d", &id);
    
    // Abre arquivo original para leitura e temporário para escrita
    f = fopen(ARQUIVO, "r");
    temp = fopen("temp.txt", "w");
    
    if(f == NULL || temp == NULL) {
        printf("Erro ao abrir arquivo!\n");
        if(f) fclose(f);
        if(temp) fclose(temp);
        return;
    }
    
    // Lê cada produto e copia para o temporário, exceto o produto a ser excluído
    while(fscanf(f, "%d;%49[^;];%29[^;];%f;%d;%49[^\n]\n", 
                 &p.id, p.nome, p.categoria, &p.preco, &p.quantidade, p.fornecedor) == 6) {
        if(p.id == id) {
            encontrado = 1;
            printf("Produto excluido: %s\n", p.nome);
            // Não grava este produto no arquivo temporário (efetua a exclusão)
        } else {
            // Grava todos os outros produtos
            fprintf(temp, "%d;%s;%s;%.2f;%d;%s\n", p.id, p.nome, p.categoria, p.preco, p.quantidade, p.fornecedor);
        }
    }
    
    fclose(f);
    fclose(temp);
    
    if(encontrado) {
        // Substitui o arquivo original pelo temporário
        remove(ARQUIVO);
        rename("temp.txt", ARQUIVO);
        printf("Produto excluido com sucesso!\n");
    } else {
        remove("temp.txt");
        printf("Produto nao encontrado!\n");
    }
}

// Exporta todos os produtos para um arquivo CSV
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
    
    // Escreve cabeçalho do CSV
    fprintf(csv, "ID,Nome,Categoria,Preco,Quantidade,Fornecedor\n");
    
    // Lê cada produto e escreve no formato CSV
    while(fscanf(f, "%d;%49[^;];%29[^;];%f;%d;%49[^\n]\n", 
                 &p.id, p.nome, p.categoria, &p.preco, &p.quantidade, p.fornecedor) == 6) {
        fprintf(csv, "%d,%s,%s,%.2f,%d,%s\n", p.id, p.nome, p.categoria, p.preco, p.quantidade, p.fornecedor);
    }
    
    fclose(f);
    fclose(csv);
    printf("Dados exportados para produtos.csv com sucesso!\n");
}

// Função principal - ponto de entrada do programa
int main() {
    int opcao;
    
    // Loop principal do menu
    do {
        // Exibe menu de opções
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
        
        // Executa a função correspondente à opção escolhida
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
    } while(opcao != 0);  // Continua até o usuário escolher sair (opção 0)
    
    return 0;  // Retorna 0 indicando execução bem-sucedida
}