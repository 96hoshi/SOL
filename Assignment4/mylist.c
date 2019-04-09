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
