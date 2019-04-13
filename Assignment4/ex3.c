/*
Scrivere un programma C che dato un file testuale come argomento, 
inserisca tutte le parole del file in una lista ordinando le parole alfabeticamente.
Ogni linea del file testuale puo' contenere piu' parole.
Fornire i metodi di creazione e gestione della lista in una libreria statica (libList.a).
Scrivere il Makefile per creare la libreria e generare l'eseguibile. 
*/
#include "mylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_STRING 1024

int main (int argc, char *argv[]){
	FILE *input = NULL;

	if (argc < 2){
		fprintf(stderr, "Non ci sono abbastanza input");
		exit(EXIT_FAILURE);
	}

	input = fopen(argv[1], "r");
	if (input == NULL){
		fprintf(stderr, "Impossibile aprire il file in lettura");
		exit(EXIT_FAILURE);
	}

	list_t *l = createList();
	// char buff[MAX_STRING];
	// while(fgets(buff, MAX_STRING, input) != NULL){
	// 	char *token = strtok(buff, " \t\n");
		
	// 	while(token){
	// 		insertList(l, token);
	// 		token = strtok(NULL, " \t\n");
	// 	}
	// }

	char token[MAX_STRING];
	while(fscanf(input, "%s", token) != EOF){
		insertList(l, token);
	}

	printList(l); 

	destroyList(l);
	fclose(input);
	return 0;
}