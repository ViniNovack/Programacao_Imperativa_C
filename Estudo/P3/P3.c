// Escreva uma função não recursiva para a liberação de todos os
// nós de uma lista ligada.

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Planeta Planeta;

struct Planeta{
    char nome[16];
    double raio;
    Planeta* proximo;
};

void liberar(Planeta* x){
    while(x != NULL){
        Planeta* auxiliar = x->proximo;
        free(x);
        x = auxiliar;
    }
}

main(){
    Planeta* L = NULL;

    Planeta* terra = (Planeta*) malloc(sizeof(Planeta));
    terra->proximo = NULL;
    L = terra;

    Planeta* venus = (Planeta*) malloc(sizeof(Planeta));
    venus->proximo = NULL;
    terra->proximo = venus;

    liberar(L);

    return 0;
}