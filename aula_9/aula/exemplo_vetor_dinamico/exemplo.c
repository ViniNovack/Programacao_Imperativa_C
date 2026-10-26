#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(){
    int capacidade = 2;
    int quantidade = 0;
    int numero;
    
    int *vetor = malloc(capacidade * sizeof(int));
    
    // quando o "malloc" falha ele retorna "NULL", por conta disso é nssesario apos usar ele
    // colocar um "if" com uma verificasao para o codigo não quebrar
    if(vetor == NULL){
        return 1;
    }
    
    printf("Digite os valores do vetor(digite 0 para finalizar o programa):\n");
    while(true){
        scanf("%d", &numero);
        
        if(numero == 0){
            break;
        }
        
        if(quantidade == capacidade){
            capacidade = capacidade * 2;
            int *tamp = realloc(vetor, capacidade * sizeof(int));
            
            if(tamp == NULL){
                free(vetor);
                return 1;
            }
            
            vetor = tamp;
        }
        
        vetor[quantidade] = numero;
        quantidade++;
    }
    
    printf("[");
    for(int i = 0; i < quantidade; i++){
        printf("%d", vetor[i]);
        
        if(i < quantidade - 1){
            printf(", ");
        }
    }
    printf("]");
    
    free(vetor);

    return 0;
}