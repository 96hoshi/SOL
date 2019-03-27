/*Scrivere un programma che prende in ingresso un intero 'N' ('N' e' piccolo, es. <=512),
 alloca in memoria una matrice di NxN elementi float in modo che siano contigui in memoria.
 Inizializzare tale matrice (chiamata ad esempio M1) in modo arbitrario (ad esempio M1(i,j) = (i+j)/2.0). 
 Fare quindi il salvataggio in un file della matrice sia in formato binario che in formato testuale 
 in modo da ottenere due file separati 'mat_dump.dat' per il formato binario e 'mat_dump.txt' per quello testuale. 
 Chiudere i file creati*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *input = NULL;
	int N = 0;
	float *M1 = NULL;

	input = fopen(argv[1],"r");
	if(N == NULL){
		fprintf(stderr, "Il file in input \"%s\" non esiste o non puo' essere aperto in lettura\n", argv[1]);
		fclose(N);
		exit(EXIT_FAILURE);
	}

	fscanf(input, "%d", &N);
	M1 = (float*) malloc((N*N) * sizeof(float));
	if(M1 == NULL){
		perror("malloc");
		exit(EXIT_FAILURE);
	}

	 for(size_t i = 0; i < N; ++i){
		for(size_t j = 0;j < N; ++j)
			M1[i* N + j] = (i+j)/2.0;
	}

	return 0;
}
