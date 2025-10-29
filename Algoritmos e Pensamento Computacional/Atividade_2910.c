#include <stdio.h>
#include <stdlib.h>

#define MAX 100

// === Funções de ordenação ===

// Bubble Sort
void bubbleSort(double v[], int n)
{
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (v[j] > v[j + 1])
            {
                double temp = v[j];
                v[j] = v[j + 1];
                v[j + 1] = temp;
            }
}

// Insertion Sort
void insertionSort(double v[], int n)
{
    for (int i = 1; i < n; i++)
    {
        double key = v[i];
        int j = i - 1;
        while (j >= 0 && v[j] > key)
        {
            v[j + 1] = v[j];
            j--;
        }
        v[j + 1] = key;
    }
}

// Selection Sort
void selectionSort(double v[], int n)
{
    for (int i = 0; i < n - 1; i++)
    {
        int min = i;
        for (int j = i + 1; j < n; j++)
            if (v[j] < v[min])
                min = j;
        double temp = v[i];
        v[i] = v[min];
        v[min] = temp;
    }
}

// Merge Sort
void merge(double v[], int l, int m, int r)
{
    int n1 = m - l + 1;
    int n2 = r - m;
    double L[n1], R[n2];

    for (int i = 0; i < n1; i++)
        L[i] = v[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = v[m + 1 + j];

    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2)
    {
        if (L[i] <= R[j])
            v[k++] = L[i++];
        else
            v[k++] = R[j++];
    }

    while (i < n1)
        v[k++] = L[i++];
    while (j < n2)
        v[k++] = R[j++];
}

void mergeSort(double v[], int l, int r)
{
    if (l < r)
    {
        int m = l + (r - l) / 2;
        mergeSort(v, l, m);
        mergeSort(v, m + 1, r);
        merge(v, l, m, r);
    }
}

// Quick Sort
void quickSort(double v[], int low, int high)
{
    if (low < high)
    {
        double pivot = v[high];
        int i = (low - 1);

        for (int j = low; j < high; j++)
        {
            if (v[j] <= pivot)
            {
                i++;
                double temp = v[i];
                v[i] = v[j];
                v[j] = temp;
            }
        }

        double temp = v[i + 1];
        v[i + 1] = v[high];
        v[high] = temp;

        int pi = i + 1;
        quickSort(v, low, pi - 1);
        quickSort(v, pi + 1, high);
    }
}

// === Funções de arquivo ===

// Grava números no arquivo "dados.txt"
void gravarDados(const char *arquivo)
{
    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo para escrita.\n");
        return;
    }

    int n;
    double numero;
    printf("Quantos números deseja gravar? ");
    scanf("%d", &n);

    for (int i = 0; i < n; i++)
    {
        printf("Digite o número %d: ", i + 1);
        scanf("%lf", &numero);
        fprintf(fp, "%.2lf\n", numero);
    }

    fclose(fp);
    printf("Arquivo '%s' criado com sucesso!\n", arquivo);
}

// Lê números do arquivo
int lerDados(const char *arquivo, double v[])
{
    FILE *fp = fopen(arquivo, "r");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo para leitura.\n");
        return 0;
    }

    int i = 0;
    while (fscanf(fp, "%lf", &v[i]) == 1 && i < MAX)
        i++;

    fclose(fp);
    return i;
}

// Grava os números ordenados em novo arquivo
void salvarOrdenado(const char *arquivo, double v[], int n)
{
    FILE *fp = fopen(arquivo, "w");
    if (fp == NULL)
    {
        printf("Erro ao abrir o arquivo para salvar ordenado.\n");
        return;
    }

    for (int i = 0; i < n; i++)
        fprintf(fp, "%.2lf\n", v[i]);

    fclose(fp);
    printf("Arquivo '%s' criado com sucesso!\n", arquivo);
}

// === Função principal ===
int main()
{
    const char *arquivoEntrada = "dados.txt";
    const char *arquivoSaida = "ordenado.txt";
    double v[MAX];
    int n, opcao, metodo;

    do
    {
        printf("\n=== MENU ===\n");
        printf("1 - Criar e gravar arquivo de dados\n");
        printf("2 - Ler e ordenar arquivo existente\n");
        printf("3 - Alterar um valor e reordenar\n");
        printf("0 - Sair\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);

        switch (opcao)
        {
        case 1:
            gravarDados(arquivoEntrada);
            break;

        case 2:
            n = lerDados(arquivoEntrada, v);
            if (n == 0)
                break;

            printf("\nEscolha o método de ordenação:\n");
            printf("1 - Bubble Sort\n");
            printf("2 - Insertion Sort\n");
            printf("3 - Selection Sort\n");
            printf("4 - Merge Sort\n");
            printf("5 - Quick Sort\n");
            printf("Opção: ");
            scanf("%d", &metodo);

            switch (metodo)
            {
            case 1:
                bubbleSort(v, n);
                break;
            case 2:
                insertionSort(v, n);
                break;
            case 3:
                selectionSort(v, n);
                break;
            case 4:
                mergeSort(v, 0, n - 1);
                break;
            case 5:
                quickSort(v, 0, n - 1);
                break;
            default:
                printf("Método inválido!\n");
                continue;
            }

            salvarOrdenado(arquivoSaida, v, n);
            break;

        case 3:
            n = lerDados(arquivoEntrada, v);
            if (n == 0)
                break;

            printf("\nArquivo atual:\n");
            for (int i = 0; i < n; i++)
                printf("[%d] %.2lf\n", i, v[i]);

            int pos;
            double novoValor;
            printf("\nDigite o índice que deseja alterar: ");
            scanf("%d", &pos);
            if (pos < 0 || pos >= n)
            {
                printf("Índice inválido!\n");
                break;
            }

            printf("Digite o novo valor: ");
            scanf("%lf", &novoValor);
            v[pos] = novoValor;

            printf("\nReordenando com Quick Sort...\n");
            quickSort(v, 0, n - 1);

            salvarOrdenado(arquivoSaida, v, n);
            break;

        case 0:
            printf("Encerrando o programa...\n");
            break;

        default:
            printf("Opção inválida!\n");
        }

    } while (opcao != 0);

    return 0;
}
