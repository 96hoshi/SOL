#include "tokenizer.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_STRING 1024

char* reverse(char* string){
	int dim = strlen(string);
	int i = 0;
	char *s = (char *) malloc(dim);

	s[dim] = '\0';
	while(dim--)
		s[i++] = string[dim];

	return s;
}

//usa strtok_r
int tokenizer_r(int argc, char *argv[]){
	FILE *input = NULL;
	FILE *output = NULL;
	int trearg = 0;
	char* buff = (char*) malloc(MAX_STRING);

	if(buff == NULL){
		perror("malloc");
		free(buff);
		return -1;
	}

	input = fopen(argv[1],"r");
	if(input == NULL){
		fprintf(stderr, "Il file in input \"%s\" non esiste o non puo' essere aperto in lettura\n", argv[1]);
		free(buff);
		fclose(input);
		return -1;
	}
	//il terzo argomento è specificato
	if(argc == 4) 
		trearg = 1;

	if(trearg && !strcmp(argv[3],"a")){		//se il terzo argomento è uguale ad 'a', "appendi"
		output = fopen(argv[2], "a");
		if(output == NULL){
			fprintf(stderr, "Il file in output \"%s\" non esiste o non puo' essere aperto in scrittura\n", argv[2]);
			fclose(output);
			fclose(input);
			free(buff);
			return -1;
		}
	} else 	{
		output = fopen(argv[2], "w");	//altrimenti sovrascrivi
		if(output == NULL){
			fprintf(stderr, "Il file in outnput \"%s\" non esiste o non puo' essere aperto in scrittura\n", argv[2]);
			fclose(output);
			fclose(input);
			free(buff);
			return -1;
		}
	}

	while(fgets(buff, MAX_STRING, input) != NULL){
		char *save = NULL;
		char *token_reversed = NULL;
		char *token = strtok_r(buff, " \n", &save);

		while (token){
			
			token_reversed = reverse(token);
			fprintf(output, "%s\n", token_reversed);
			token = strtok_r(NULL, " \n", &save);
			free(token_reversed);
		}
	}

	free(buff);
	fclose(input);
	fclose(output);
	return 0;
}





//usa strtok
int tokenizer(int argc, char *argv[]){
	FILE *input = NULL;
	FILE *output = NULL;
	int trearg = 0;
	char* buff = (char*) malloc(MAX_STRING);

	if(buff == NULL){
		perror("malloc");
		free(buff);
		return -1;
	}

	input = fopen(argv[1],"r");
	if(input == NULL){
		fprintf(stderr, "Il file in input \"%s\" non esiste o non puo' essere aperto in lettura\n", argv[1]);
		free(buff);
		fclose(input);
		return -1;
	}
	//il terzo argomento è specificato
	if(argc == 4) 
		trearg = 1;

	if(trearg && !strcmp(argv[3],"a")){		//se il terzo argomento è uguale ad 'a', "appendi"
		output = fopen(argv[2], "a");
		if(output == NULL){
			fprintf(stderr, "Il file in output \"%s\" non esiste o non puo' essere aperto in scrittura\n", argv[2]);
			fclose(output);
			fclose(input);
			free(buff);
			return -1;
		}
	} else 	{
		output = fopen(argv[2], "w");	//altrimenti sovrascrivi
		if(output == NULL){
			fprintf(stderr, "Il file in outnput \"%s\" non esiste o non puo' essere aperto in scrittura\n", argv[2]);
			fclose(output);
			fclose(input);
			free(buff);
			return -1;
		}
	}

	while(fgets(buff, MAX_STRING, input) != NULL){
		char *token_reversed = NULL;
		char *token = strtok(buff, " \n");

		while (token){
			
			token_reversed = reverse(token);
			fprintf(output, "%s\n", token_reversed);
			token = strtok(NULL, " \n");
			free(token_reversed);
		}
	}

	free(buff);
	fclose(input);
	fclose(output);
	return 0;
}