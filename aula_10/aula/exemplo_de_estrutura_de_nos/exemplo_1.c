#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

// Estrutura de um nó da árvore
typedef struct Nodo Nodo;
struct Nodo{
    int valor;            // dado armazenado em cada nó da árvore
    Nodo* esquerda;       // ponteiro para a raiz da sub-árvore à esquerda
    Nodo* direito;        // ponteiro para a raiz da sub-árvore à direita
};
// Ponteiro para a raiz da árvore
Nodo* arvore = NULL; // árvore inicialmente vazia

void imprimir(Nodo* p){
/*
    Função para imprimir os valores contidos nos nós de uma sub-árvore
    Parâmetro:
        p: ponteiro para a raiz da sub-árvore
*/
    // imprime recursivamente a sub-árvore à esquerda, se existir
    if(p -> esquerda != NULL){
        imprimir(p -> esquerda);
    }

    // imprime o dado contido na raiz da sub-árvore
    printf("%d ", p -> valor);

    // imprime recursivamente a sub-árvore à direita, se existir
    if(p -> direito != NULL){
        imprimir(p -> direito);
    }
}

Nodo* busca(Nodo* p, int chave){
/*
    Função para encontrar o nó de uma sub-árvore que contém certo valor
    Retorno: um ponteiro para nó encontrado ou NULL, se não existir
    Parâmetros:
        p: ponteiro para a raiz da sub-árvore
        chave: valor a ser encontrado
*/
    Nodo* resposta = NULL;
    if(chave == p -> valor){
        resposta = p; //encontrado!
    } else if(chave < p -> valor){
        // deve buscar à esquerda de p
        if(p -> esquerda != NULL){
            resposta = buscar(p -> esquerda, chave);
        }
    } else{
        // deve buscar à direita de p
        if(p -> direito != NULL){
            resposta = buscar(p -> direito, chave);
        }
    }
    return resposta;
}

void inserir_dado(int novo_valor){
/*
    Função para inserir um novo dado na árvore
    Parâmetro:
        novo_valor: dado a ser inserido
*/
    // cria um novo nó para armazenar o dado
    Nodo* q = (Nodo*) calloc(1, sizeof(Nodo));
    q -> valor = novo_valor;
    q -> esquerda = NULL;
    q -> direito = NULL;

    if(arvore == NULL){     // árvore vazia?
        arvore = q;  // primeiro nó da árvore(a raiz)
    } else{
        inserir(arvore, q); // insere o novo nó na árvore
    }
}

void inserir(Nodo* p, Nodo* q){
/*
    Função para inserir um novo nó em uma sub-árvore mantendo-a ordenada
    Parâmetro:
        p: ponteiro para a raiz sa sub-árvore
        q: ponteiro para o novo nó a ser inserido
*/
    if(q -> valor < p -> valor){
        // insere à esquerda de p
        if(p -> esquerda != NULL){ //existe filho à esquerda?
            inserir(p -> esquerda, q); // insere recursivamente à esquerda
        } else{
            p -> esquerda = q; // insere aqui
        }
    } else{
        // insere à direita de p
        if(p -> direito != NULL){  // existe filho à direita?
            inserir(p -> direito, q);   // insere recursivamente à direita
        } else{
            p -> direito = q; // insere aqui
        }
    }
}