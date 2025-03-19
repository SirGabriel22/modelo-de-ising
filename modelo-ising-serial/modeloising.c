#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "funcoesising.h"
#include <time.h>
#include <omp.h>

int main(void){
    int **matriz1, **matriz2;
    clock_t inicio = clock();

    // Alocação da primeira matriz

    matriz1 = malloc(L*sizeof(int*));
    for(int i = 0; i < L; i++)
        matriz1[i] = malloc(L*sizeof(int));

    // Alocação da segunda matriz

    matriz2 = malloc((L)*sizeof(int*));
    for(int i = 0; i < (L); i++)
        matriz2[i] = malloc(L*sizeof(int));

    // A primeira matriz é inicializada de forma aleatória com spins 1 e -1, estritamente. 

    inicializaSpins(matriz1, L, L);

    // Impressão da malha.
    printf("\nMalha:\n");
    imprimeMatriz(matriz1, L, L);

    printf("\n");

    matriz2 = ising(matriz1, L, L);

    printf("\nEstado final da malha:\n");

    imprimeMatriz(matriz2, L, L);

    clock_t fim = clock();

    double tempo = (double) (fim - inicio)/CLOCKS_PER_SEC;
 
    printf("\nO tempo de execução foi de %lf segundos.", tempo);
}