/*
Realizzare quindi lo stesso programma, utilizzando le chiamate di libreria fread ed fwrite.
Chiamiamo questa seconda versione 'mycp_std'. 
Confrontare le prestazioni (usando il comando time) 
del programma 'mycp_sc' e 'mycp_std' al variare del parametro 'buffersize' 
(provare un po' di casi: 1 4 8 16 32 ….. 8192). Che cosa si nota ?
*/

#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[])
{
	size_t buffersize = 256;
	int read_l = 0, write_l = 0;
	FILE *input = NULL;
	FILE *output = NULL;

	if (argc < 3) {
		perror("Non ci sono abbastanza argomenti");
		exit(EXIT_FAILURE);
	}
	if (argc > 3)
		buffersize = (size_t) strtol(argv[3], NULL, 10);

	input = fopen(argv[1], "r");
	if (input == NULL) {
		perror("Impossibile aprire fle di input");
		exit(EXIT_FAILURE);
	}

	output = fopen(argv[2], "w");
	if (output == NULL) {
		perror("Impossibile aprire fle di output");
		fclose(input);
		exit(EXIT_FAILURE);
	}

	char *buffer = malloc(buffersize * sizeof(char));

	read_l = fread(buffer, sizeof(*buffer), buffersize, input);
		// perror(" Errore in scrittura");
		// close(input);
		// close(output);
		// exit(EXIT_FAILURE);

	write_l = fwrite(buffer, sizeof(*buffer), read_l, output);
	// 	perror("Errore in lettura");
	// 	close(input);
	// 	close(output);
	// 	exit(EXIT_FAILURE);

	free(buffer);
	fclose(input);
	fclose(output);
	return 0;
}
