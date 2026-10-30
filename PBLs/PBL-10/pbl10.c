#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINHA 256
#define MAX_NOME 128

/* Dados de uma pessoa */
typedef struct {
    int codigo;
    float altura;
    char nome[MAX_NOME];
} Pessoa;

/* Lista familia (vetor dinamico) */
typedef struct {
    Pessoa *itens;
    int tamanho;
    int capacidade;
} Lista;

/* No da arvore de indexacao e busca: guarda a posicao da pessoa na lista */
typedef struct No {
    int indice;
    struct No *esq;
    struct No *dir;
} No;

/* ---------- Lista ---------- */

void lista_iniciar(Lista *l) {
    l->itens = NULL;
    l->tamanho = 0;
    l->capacidade = 0;
}

void lista_inserir(Lista *l, Pessoa p) {
    if (l->tamanho == l->capacidade) {
        int nova = (l->capacidade == 0) ? 8 : l->capacidade * 2;
        Pessoa *tmp = realloc(l->itens, nova * sizeof(Pessoa));
        if (tmp == NULL) {
            fprintf(stderr, "Erro de memoria.\n");
            exit(1);
        }
        l->itens = tmp;
        l->capacidade = nova;
    }
    l->itens[l->tamanho++] = p;
}

void lista_liberar(Lista *l) {
    free(l->itens);
    l->itens = NULL;
    l->tamanho = l->capacidade = 0;
}

/* Remove espacos e quebras de linha do fim da string */
void remover_fim(char *s) {
    int n = (int)strlen(s);
    while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r' || s[n - 1] == ' ' || s[n - 1] == '\t'))
        s[--n] = '\0';
}

/* Le o arquivo texto: codigo, altura e nome em cada linha */
int lista_ler_arquivo(Lista *l, const char *caminho) {
    FILE *f = fopen(caminho, "r");
    if (f == NULL) return 0;

    char linha[MAX_LINHA];
    while (fgets(linha, sizeof(linha), f) != NULL) {
        Pessoa p;
        int consumidos = 0;
        if (sscanf(linha, "%d %f %n", &p.codigo, &p.altura, &consumidos) >= 2) {
            strncpy(p.nome, linha + consumidos, MAX_NOME - 1);
            p.nome[MAX_NOME - 1] = '\0';
            remover_fim(p.nome);
            lista_inserir(l, p);
        }
    }
    fclose(f);
    return 1;
}

void imprimir_pessoa(int posicao, Pessoa p) {
    printf("[%2d] (%2d) (%.1f) %s\n", posicao, p.codigo, p.altura, p.nome);
}

void lista_imprimir(const Lista *l) {
    for (int i = 0; i < l->tamanho; i++)
        imprimir_pessoa(i, l->itens[i]);
}

/* ---------- Arvores ---------- */

/* Comparacao por codigo */
int cmp_codigo(const Pessoa *a, const Pessoa *b) {
    return a->codigo - b->codigo;
}

/* Comparacao por altura (desempate pelo codigo, para ordem estavel e previsivel) */
int cmp_altura(const Pessoa *a, const Pessoa *b) {
    if (a->altura < b->altura) return -1;
    if (a->altura > b->altura) return 1;
    return a->codigo - b->codigo;
}

No *arvore_inserir(No *raiz, const Lista *l, int indice,
                   int (*cmp)(const Pessoa *, const Pessoa *)) {
    if (raiz == NULL) {
        No *n = malloc(sizeof(No));
        if (n == NULL) {
            fprintf(stderr, "Erro de memoria.\n");
            exit(1);
        }
        n->indice = indice;
        n->esq = n->dir = NULL;
        return n;
    }
    if (cmp(&l->itens[indice], &l->itens[raiz->indice]) < 0)
        raiz->esq = arvore_inserir(raiz->esq, l, indice, cmp);
    else
        raiz->dir = arvore_inserir(raiz->dir, l, indice, cmp);
    return raiz;
}

No *arvore_criar(const Lista *l, int (*cmp)(const Pessoa *, const Pessoa *)) {
    No *raiz = NULL;
    for (int i = 0; i < l->tamanho; i++)
        raiz = arvore_inserir(raiz, l, i, cmp);
    return raiz;
}

/* Percurso em ordem (esquerda, raiz, direita): ordem nao decrescente */
void arvore_imprimir_em_ordem(const No *raiz, const Lista *l, int *contador) {
    if (raiz == NULL) return;
    arvore_imprimir_em_ordem(raiz->esq, l, contador);
    imprimir_pessoa((*contador)++, l->itens[raiz->indice]);
    arvore_imprimir_em_ordem(raiz->dir, l, contador);
}

void arvore_liberar(No *raiz) {
    if (raiz == NULL) return;
    arvore_liberar(raiz->esq);
    arvore_liberar(raiz->dir);
    free(raiz);
}

/* ---------- Programa principal ---------- */

int main(int argc, char *argv[]) {
    const char *caminho = (argc > 1) ? argv[1] : "familia.txt";

    Lista familia;
    lista_iniciar(&familia);

    /* 1) Leitura do arquivo para a lista familia */
    if (!lista_ler_arquivo(&familia, caminho)) {
        fprintf(stderr, "Nao foi possivel abrir o arquivo '%s'.\n", caminho);
        return 1;
    }

    /* 2) Impressao da lista familia */
    printf("Pessoas da familia na ordem lida do arquivo texto:\n");
    lista_imprimir(&familia);

    /* 3) Arvore T1 por codigo */
    No *T1 = arvore_criar(&familia, cmp_codigo);

    /* 4) Impressao em ordem de codigo usando T1 */
    printf("\nPessoas da familia em ordem de codigo:\n");
    int contador = 0;
    arvore_imprimir_em_ordem(T1, &familia, &contador);

    /* 5) Arvore T2 por altura */
    No *T2 = arvore_criar(&familia, cmp_altura);

    /* 6) Impressao em ordem de altura (usando a arvore de altura, T2) */
    printf("\nPessoas da familia em ordem de altura:\n");
    contador = 0;
    arvore_imprimir_em_ordem(T2, &familia, &contador);

    arvore_liberar(T1);
    arvore_liberar(T2);
    lista_liberar(&familia);
    return 0;
}
