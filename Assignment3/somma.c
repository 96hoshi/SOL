/* La funzione 'somma' aggiunge l'intero x letto da un file che contiene un intero per ogni riga al valore calcolato fino a quel momento,
 quindi ritorna la somma. Il nome del file è passato come argomento al main.
 Il valore iniziale della somma deve essere 'INIT_VALUE' che viene definito a compilazione utilizzando il flag del compilatore -D 
 (es. -DINIT_VALUE=100). Il programma non deve fare uso di variabili globali.
*/
#include <stdio.h>
#include <stdlib.h>

#define MAX_STRING 1024

/*funzione che utilzza INIT_VALUE definito a compilazione*/
int somma(int x) {
	int static acc = 0;

	acc += x + INIT_VALUE;
	return acc;
}

int main(int argc, char *argv[]){
	FILE* input = NULL;
	int x = 0, res = 0;

	input = fopen(argv[1],"r");
	if(input == NULL){
		fprintf(stderr, "Il file in input \"%s\" non esiste o non puo' essere aperto in lettura\n", argv[1]);
		fclose(input);
		return -1;
	}

	while(fscanf(input, "%d", &x)==1)
		res = somma(x);

	printf("%d\n", res);

	fclose(input);
	return 0;
}