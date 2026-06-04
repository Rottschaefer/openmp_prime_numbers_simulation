#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <omp.h>

#define N 500000000
#define CHUNK_SIZE 10
#define NUM_THREADS 4

int primo (long int n) {
	long int i;
       
	for (i = 3; i < (long int)(sqrt(n) + 1); i+=2) 
	     if (n%i == 0) 
	         return 0;
	return 1;
}

int main() { /* primos_seq.c  */
double t_inicio, t_fim;
long int i, total = 0;


    t_inicio = omp_get_wtime();

    
#pragma omp parallel for reduction(+:total) schedule(guided,CHUNK_SIZE) num_threads(NUM_THREADS) 
    for (i = 3; i <= N; i += 2) 	
         if(primo(i) == 1) total++;
		
    total += 1;    /* Acrescenta o dois, que também é primo */
    t_fim = omp_get_wtime();
    printf("Quant. de primos entre 1 e %ld: %ld \n", N, total);
    printf("Tempo de execução: %f \n", t_fim-t_inicio);
    return(0);
}
