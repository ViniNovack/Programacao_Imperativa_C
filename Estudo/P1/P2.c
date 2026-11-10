#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>

int main(){
    FILE* dados = fopen("P1.exe", "rb");
    FILE* texto_2 = fopen("texto_2", "w");

    int valor;
    while(!feof(dados)){
        fread(&valor, sizeof(int), 1, dados);
        fprintf(texto_2, "%d\n", valor);
    }

    fclose(dados);
    fclose(texto_2);
    return 0;
}