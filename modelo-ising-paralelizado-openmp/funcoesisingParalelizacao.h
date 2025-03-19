#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <omp.h>

#define BOL 1.0 // Constante de Boltzmann
#define J 2 // Coeficiente de interação 
#define L 15 // Tamanho das linhas e colunas da matriz
#define MAXITER 2e+6 // Número de iterações para o passo de Monte Carlo

int inicializaSpins(int **mat, int m, int n){

        for(int i = 0; i < m; i++){

            for (int j = 0; j < n; j++)
                mat[i][j] = (rand() % 2) * 2 - 1;

        }
    //printf("\nNúmero de elementos: %d", m*n);
    return 1;//Funcionou.
}

int **copiaMatriz(int **mat, int m, int n){//Função que copia matriz

    int i, j, **aux;

    aux = malloc(m*sizeof(int*)); // Primeira alocação
    for(i = 0; i < m; i++) 
        aux[i] = malloc(n*sizeof(int)); // Segunda alocação

    for(i = 0; i < m; i++){
    
        for(j = 0; j < n; j++){
    
            aux[i][j] = mat[i][j]; // Processo simples de cópia
    
            }
    
        }
    
    return aux; // O retorno é uma matriz.
    
    for(i = 0; i < m; i++)
        free(aux[i]); // Liberação da memória para evitar dados residuais.
    
    free(aux); // A mesma coisa.

}

void imprimeMatriz(int **mat, int m, int n){//Impressão da matriz

    for (int i = 0; i < m; i++){

        for (int j = 0; j < n; j++){

            printf("%d\t", mat[i][j]); // Impressão simples
        
        }
        
        printf("\n");
    
    }

}

double variaEnergia(int **mat, int m, int n){ // Funcionou

    int norte = mat[(m + L - 1) % L][n]; // spin acima
    int sul =   mat[(m + 1) % L][n];     // spin abaixo
    int leste = mat[m][(n + 1) % L];     // spin à direita
    int oeste = mat[m][(n + L - 1) % L]; // spin à esquerda

    return -J * mat[m][n] * (norte + sul + leste + oeste); // Retorna a variação

}

double probabilidade(int **mat, int m, int n, double T){

    return exp(-variaEnergia(mat, m, n)/(BOL*T)); 

}

double magnetizacao(int **mat, int m, int n){

    double magnetiza = 0.0;

    for(int i = 0; i < m; i++){

        for(int j = 0; j < n; j++){
        
        magnetiza += mat[i][j]; // Soma todos os spins da malha
        
        }

    }

    return magnetiza/(m*n); // Retorna dividindo pela qtd de linhas e colunas.
}

double energiaTotal(int **mat, int m, int n){//Energia total da malha

    double energia = 0.0;

    for(int i = 0; i < m;  i++){

        for(int j = 0; j < n; j++){

            int norte = mat[(i + L - 1) % L][j]; // spin acima
            int sul   = mat[(i + 1) % L][j];     // spin abaixo
            int leste = mat[i][(j + 1) % L];     // spin à direita
            int oeste = mat[i][(j + L - 1) % L]; // spin à esquerda

            int soma = norte + sul + leste + oeste;
            
            energia+=(-J*mat[i][j]*soma); // Análogo à variação de energia por sítio.
        }
    }
    return energia/(2*m*n); /*Dividimos por 2 para evitar duplicação de dados.*/
}

void metropolis(int **mat, int m, int n, double T){

    int a = rand() % m; //Número aleatório menor que m.
    int b = rand() % n; //O mesmo, mas com n.

    double delta = variaEnergia(mat, a, b); // Cálculo da variação de energia.

    if((delta < 0) ||  (rand() / (double)RAND_MAX) < probabilidade(mat, a, b, T))
        mat[a][b] *= (-1);

}

int **ising(int **mat, int m, int n){
    
    int **mat1;
    double mg1, mg2, en1, en2, aux;

    FILE *fp = fopen("dados2.dat", "w");
    if(fp == NULL){
        printf("\nErro ao abrir arquivo!\n");
        exit(EXIT_FAILURE);
    }

    mat1 = malloc(m*sizeof(int*));
    for(int i = 0; i < m; i++)
        mat1[i] = malloc(n*sizeof(int));

    mat1 = copiaMatriz(mat, m, n);
    
    //Cabeçalho do arquivo

    fprintf(fp, "Temperatura\tMagnetizacao\tEnergia\tCalor Especifico\tSuscetibilidade Magnética\n");

        #pragma omp parallel for private(aux) reduction(+:mg1, mg2, en1, en2)
        for (int temp = 1; temp < 201; temp++) {
            aux = 1.0 + 0.01 * temp;

            int **mat2 = copiaMatriz(mat1, m, n); // Cópia local de mat1

            mg1 = mg2 = en1 = en2 = 0.0;

            // Equilibração
            for (int i = 0; i < MAXITER / 10; i++)
                metropolis(mat2, m, n, aux);

            // Iterações de Monte Carlo
            for (int i = 0; i < MAXITER; i++) {

                metropolis(mat2, m, n, aux);
                
                mg1 += fabs(magnetizacao(mat2, m, n));
                mg2 += magnetizacao(mat2, m, n) * magnetizacao(mat2, m, n);
                
                en1 += energiaTotal(mat2, m, n);
                en2 += energiaTotal(mat2, m, n) * energiaTotal(mat2, m, n);
            }

            // Cálculo de propriedades físicas
            double calor = (((en2 / MAXITER) - ((en1 / MAXITER) * (en1 / MAXITER))) / (aux * aux)) * (m * n);
            double susce = (((mg2 / MAXITER) - ((mg1 / MAXITER) * (mg1 / MAXITER))) / fabs(aux)) * (m * n);

            // Gravação no arquivo protegido por critical
            #pragma omp critical
            {
                fprintf(fp, "\n%g\t%g\t%g\t%g\t%g\n", aux, fabs(mg1 / MAXITER), en1 / MAXITER, calor, susce);
            }

            // Liberação da cópia local
            for (int i = 0; i < m; i++)
                free(mat2[i]);
            free(mat2);
        }

    return mat1;

    for(int i = 0; i < m; i++)
        free(mat1[i]);

    free(mat1);

    fclose(fp);
}