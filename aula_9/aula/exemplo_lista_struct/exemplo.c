#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

typedef struct Planeta{
    char nome[16];
    double raio;
    double distancia_do_sol;
    
    struct Planeta *proximo;
} Planeta;

int main(){
    Planeta *terra = calloc(1, sizeof(Planeta));
    if(terra == NULL){
        return 1;
    }
    
    strcpy(terra -> nome, "Terra");
    terra -> raio = 6378.0;
    terra -> distancia_do_sol = 149600000.0;
    terra -> proximo = NULL;
    
    
    Planeta *marte = calloc(1, sizeof(Planeta));
    if(marte == NULL){
        free(terra);
        return 1;
    }
    
    strcpy(marte -> nome, "Marte");
    marte -> raio = 3397.0;
    marte -> distancia_do_sol = 2274900000.0;
    marte -> proximo = terra;
    
    
    
    Planeta *p = marte;
    while(p != NULL){
        printf("%s\n", p -> nome);
        p = p -> proximo;
    }
    
    return 0;
}