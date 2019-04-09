#include "mylist.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

list_t *createList(){  // crea una lista vuota
	list_t *L = malloc(sizeof(list_t));
	return L;
}

void printList(list_t *L){ // stampa tutta la lista
	if(L == NULL)
		return;

	node_t *tmp = *L;
	while(tmp != NULL){
		if(tmp->string != NULL)
			printf("%s\n", tmp->string);
		tmp = tmp->next;
	}
}

int destroyList(list_t *L){ // libera tutta la memoria allocata dalla lista
	if(L == NULL)
		return -1;

	node_t *head = *L;
	while(head != NULL){
		if(head->string != NULL)
			free(head->string);
		node_t *tmp = head;
		head = head->next;
		free(tmp);
	}
	free(L);
	return 0;
}  

int insertList(list_t *L, const char * str){ // inserisce una parola nella lista
	if(L == NULL)
		return -1;

	node_t * new = (node_t *)malloc(sizeof(node_t));
	new->next = NULL;
	if(str != NULL){
		new->string = (char *)malloc(strlen(str) + 1);
		strcpy(new->string, str);
	} else{ 
		new->string = NULL;
	}

	if(*L == NULL){
		*L = new;
		return 0;
	}

	node_t *prev = NULL;
	node_t *curr = *L;
	while(curr != NULL){
		if(strcmp(str,curr->string) <= 0){
			if(prev != NULL){
				prev->next = new;
				new->next = curr;
			} else{
				*L = new;
				new->next = curr;
			}
			return 0;
		}
		prev = curr;
		curr = curr->next;
	}
	prev->next = new;

	return 0;
}

// typedef struct list {
// 	char *string;
// 	struct list *next;
// } list_t;

// list_t *createList(){			// crea una lista vuota
// 	list_t *l = malloc(sizeof(list_t));

// 	l->string = NULL;
// 	l->next = NULL;

// 	return l;
// }  

// int destroyList(list_t *L){ // libera tutta la memoria allocata dalla lista
// 	int count = 0;

// 	while (L != NULL){
// 		list_t *tmp = L;
// 		L =  L->next;

// 		if(tmp->string == NULL) //TODO: NON SI FA!!! -ti riferisci al controllo?
// 			count++; 			//count conta il numero di parole NULL nella lista
// 		else free(tmp->string);

// 		free(tmp);
// 	}
// 	return 0;
// }    

// int insertList(list_t *L, const char * str){  // inserisce una parola nella lista
// 	size_t dim = strlen(str);
// 	list_t * new = createList();

// 	new->string = (char*)malloc(dim);
// 	if(new->string == NULL){
// 		perror("insertList malloc has stopped working");
// 		return -1;
// 	}
// 	strncpy(new->string, str, dim); //TODO: USA LA VERSIONE SAFE -(risolto?)
// 	//new->next = NULL; TODO: HA SENSO??? -no :v

// 	list_t *prev = NULL;
// 	list_t *curr = L;
// 	if(curr == NULL){
// 	//caso: inserzione in lista vuota
// 		&L = new; //TODO:funzia???
// 		return 0; //HINT: Usa un nodo vuoto per tenere un puntatore alla lista. 
// 				  //      Tienine conto quando fai la print list
// 	}
// 	while(curr != NULL){
// 		if(strcmp(curr->string, new->string) < 0){ //elemento lista corrente >= quello da inserire
// 			if(prev == NULL){
// 	//caso: primo elemento di una lista non vuota
// 				&L = new; //funzia???
// 				new->next = curr;
// 			} else{
// 	//caso: elemento in mezzo alla lista
// 				prev->next = new;
// 				new->next = curr;
// 			}
// 			return 0;
// 		}
// 		//scorro la lista
// 		prev = curr;
// 		curr = curr->next;
// 	}
// 	//caso: arrivo fino alla fine, è l'ultimo elemento
// 	prev->next = new;
// 	return 0;
// }

// void printList(list_t *L){ // stampa tutta la lista
// 	list_t *curr = L;

// 	while (curr != NULL){
// 		if(curr->string != NULL) //HINT: Controlla HINT che si trova in insertList -still non so come possa funziare
// 			printf("%s\n", curr->string);
// 		curr = curr->next;
// 	}
// }                 
