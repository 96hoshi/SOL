#ifndef MYLIST_H
#define MYLIST_H

typedef struct node {
	char *string;
	struct node *next;
} node_t;

typedef node_t * list_t;

list_t *createList();                         // crea una lista vuota
int     destroyList(list_t *L);               // libera tutta la memoria allocata dalla lista
int     insertList(list_t *L, const char *);  // inserisce una parola nella lista
void    printList(list_t *L);                 // stampa tutta la lista

#endif