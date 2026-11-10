#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(){
    FILE* texto = fopen("texto.txt", "w");
    FILE* dados = fopen("dados.bin", "bw");

    int valor = 123456789;

    fprintf(texto, "%d", valor);

    valor = 0;
    while(!feof(texto)){
        fscanf(texto, "%d", &valor);
        fwrite(&valor, sizeof(int), 1, dados);
    }

    fclose(texto);
    fclose(dados);
    return 0;
}