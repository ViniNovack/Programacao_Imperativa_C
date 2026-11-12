// Complete o programa a seguir tal que todos os dados contidos no vetor valores sejam escritos em um
// arquivo binário denominado dados.bin

#include <stdio.h>

int main()
{
    double valores[] = { 4.5, 8.3, 9.0, 5.4, 2.7 };

    int K = sizeof(double);
    int N = sizeof(valores)/K;

    FILE* dados = ("dados.bin", "wb");

    fwrite(valores, K, N, dados);

    fclose(valores);

    return 0;
}