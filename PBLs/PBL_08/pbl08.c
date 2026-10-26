#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_PESSOAS 1000
#define MAX_NOME 100
#define MAX_LINHA 256

typedef struct {
    int codigo;
    char nome[MAX_NOME];
} Pessoa;

/* Lê o arquivo texto e preenche o vetor; retorna a quantidade de pessoas lidas. */
int lerArquivo(const char *nomeArquivo, Pessoa familia[]) {
    FILE *arq = fopen(nomeArquivo, "r");
    char linha[MAX_LINHA];
    int n = 0;

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomeArquivo);
        return -1;
    }

    while (n < MAX_PESSOAS && fgets(linha, sizeof(linha), arq) != NULL) {
        linha[strcspn(linha, "\r\n")] = '\0';
        if (sscanf(linha, "%d %99[^\n]", &familia[n].codigo, familia[n].nome) == 2) {
            n++;
        }
    }

    fclose(arq);
    return n;
}

void imprimir(const char *titulo, Pessoa familia[], int n) {
    int i;
    printf("%s\n", titulo);
    for (i = 0; i < n; i++) {
        printf("[%2d] (%2d) %s\n", i, familia[i].codigo, familia[i].nome);
    }
    printf("\n");
}

/* Compara duas pessoas pelo código. */
int compararCodigo(Pessoa a, Pessoa b) {
    return a.codigo - b.codigo;
}

/* Compara duas pessoas pelo nome. */
int compararNome(Pessoa a, Pessoa b) {
    return strcmp(a.nome, b.nome);
}

/* Intercala v[inicio..meio] e v[meio+1..fim], ambos já ordenados. */
void merge(Pessoa v[], Pessoa aux[], int inicio, int meio, int fim,
           int (*comparar)(Pessoa, Pessoa)) {
    int i = inicio, j = meio + 1, k = inicio;

    while (i <= meio && j <= fim) {
        if (comparar(v[i], v[j]) <= 0) {
            aux[k++] = v[i++];
        } else {
            aux[k++] = v[j++];
        }
    }
    while (i <= meio) {
        aux[k++] = v[i++];
    }
    while (j <= fim) {
        aux[k++] = v[j++];
    }
    for (k = inicio; k <= fim; k++) {
        v[k] = aux[k];
    }
}

/* Merge sort recursivo. */
void mergeSort(Pessoa v[], Pessoa aux[], int inicio, int fim,
               int (*comparar)(Pessoa, Pessoa)) {
    if (inicio < fim) {
        int meio = (inicio + fim) / 2;
        mergeSort(v, aux, inicio, meio, comparar);
        mergeSort(v, aux, meio + 1, fim, comparar);
        merge(v, aux, inicio, meio, fim, comparar);
    }
}

int main(void) {
    Pessoa familia[MAX_PESSOAS];
    Pessoa aux[MAX_PESSOAS];
    int n = lerArquivo("familia.txt", familia);

    if (n < 0) {
        return 1;
    }

    imprimir("Pessoas da família na ordem lida do arquivo texto:", familia, n);

    mergeSort(familia, aux, 0, n - 1, compararCodigo);
    imprimir("Pessoas da família em ordem de código:", familia, n);

    mergeSort(familia, aux, 0, n - 1, compararNome);
    imprimir("Pessoas da família em ordem de nome:", familia, n);

    return 0;
}
