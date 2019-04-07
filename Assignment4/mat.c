/*
 Scrivere un programma che prende in ingresso un intero 'N' 
 ('N' e' piccolo, es. <=512), alloca in memoria una matrice di NxN elementi 
 float in modo che siano contigui in memoria.
 Inizializzare tale matrice (chiamata ad esempio M1) in modo arbitrario
 (ad esempio M1(i,j) = (i+j)/2.0). 
 Fare quindi il salvataggio in un file della matrice sia in formato binario che
 in formato testuale in modo da ottenere due file separati 'mat_dump.dat' per il
 formato binario e 'mat_dump.txt' per quello testuale. 
 Chiudere i file creati
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	FILE *output_dat = NULL;
	FILE *output_txt = NULL;
	int N = 0;
	float *M1 = NULL;

	if(argc < 2){
		fprintf(stderr, "Non ci sono abbastanza input");
		exit(EXIT_FAILURE);	
	}

	N = (int)strtol(argv[1], NULL, 10);

	M1 = (float*) malloc((N * N) * sizeof(float));
	for(size_t i = 0; i < N; ++i)
		for(size_t j = 0; j < N; ++j)
			M1[i * N + j] = (i + j)/2.0;
	
	output_dat = fopen("output.dat", "w");
	if(output_dat == NULL){
		fprintf(stderr, "output_dat");
		fclose(output_dat);
		exit(EXIT_FAILURE);
	}	

	fwrite(M1, sizeof(*M1), N * N, output_dat);
	fclose(output_dat);

	output_txt = fopen("output.txt", "w");
	if(output_txt == NULL){
		fprintf(stderr, "output_txt");
		fclose(output_txt);
		exit(EXIT_FAILURE);
	}

	/*
	for(size_t i = 0; i < N * N; ++i)
 		fprintf(output_txt, "%f\t", M1[i] );
 	*/
	for(size_t i = 0; i < N; ++i)
		for(size_t j = 0; j < N; ++j)
			fprintf(output_txt, "%f\t", M1[i * N + j]);
	fclose(output_txt);

	free(M1);

	return 0;
}
