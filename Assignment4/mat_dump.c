/*
Scrivere un secondo programma (oppure estendere quello precedente) che prende in
 ingresso i nomi dei due file creati in precedenza e l'intero 'N', legge la 
 matrice sia dal file 'mat_dump.dat' che dal file 'mat_dump.txt' memorizzandone 
 il contenuto in due matrici distinte. Al termine dell'operazione di lettura, 
 effettua il confronto delle due matrici con la funzione 'confronta' che deve 
 essere implementata in modo “generico” cioe' deve prendere come argomenti un 
 puntatore a funzione con tipo opportuno, i puntatori alle due matrici da 
 confrontare e la size delle matrici. Il programma deve stampare l'esito del 
 confronto. Testare il programma passando alla funzione 'confronta' la funzione 
 di libreria memcmp (man 3 'memcmp'). 

Argomenti: un puntatore a funzione con tipo opportuno, 
i puntatori alle due matrici da confrontare e la size delle matrici.
Il programma deve stampare l'esito del confronto.
Testare il programma passando alla funzione 'confronta' la funzione di libreria memcmp.
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

unsigned char confronta(int (*cmp)(const float *, const float *, size_t), float *dat_mat, float *txt_mat, int dim){
	return cmp(dat_mat, txt_mat, dim * dim * sizeof(float));
}

int main(int argc, char *argv[]){

	FILE *dat_file = NULL;
	FILE *txt_file = NULL;
	int N = 0;
	float *dat_matrix = (float*) malloc((N * N) * sizeof(float));
	float *txt_matrix = (float*) malloc((N * N) * sizeof(float));

	if(argc < 4){
		fprintf(stderr, "Non ci sono abbastanza input");
		exit(EXIT_FAILURE);	
	}

	dat_file = fopen(argv[1], "r");	
	if(dat_file == NULL){
		fprintf(stderr, "Impossibile aprire il file in lettura");
		fclose(dat_file);
		exit(EXIT_FAILURE);
	}	

	txt_file = fopen(argv[2], "r");
	if(txt_file == NULL){
		fprintf(stderr, "Impossibile aprire il file in lettura");
		fclose(dat_file);
		fclose(txt_file);
		exit(EXIT_FAILURE);
	}	

	N = (int)strtol(argv[3], NULL, 10);

	fread(dat_matrix, sizeof(*dat_matrix), N * N, dat_file);

	// for(size_t i = 0; i < N; i++)
	// 	for(size_t j = 0; j < N; j++)
	// 		fscanf(txt_file, "%f", &txt_matrix[i * N + j]);

	for(size_t i = 0; i < N * N; ++i)
 		fscanf(txt_file, "%f", &txt_matrix[i] );


	unsigned char res = confronta(memcmp, dat_matrix, txt_matrix, N);
	printf("%u\n", res);

	fclose(dat_file);
	fclose(txt_file);
	free(txt_matrix);
	free(dat_matrix);
	return 0;
}
