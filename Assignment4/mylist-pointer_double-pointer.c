/*OVERVIEW: lista di parole in ordine alfabetico crescente dove in testa ho
 la stringa "più piccola" secondo strcmp
 il valore passato alle funzioni è un doppio puntatore alla testa
*/

typedef struct node {
	char* string;
	struct node *next;
} node_t;

typedef node_t * list_t; 

/*
	EFFECTS: inizializzo un elemento di tipo list_t* con i parametri nulli:
	string = null
	next = null
	MODIFIES: this, testa
	RETURN: l'elemento creato
*/
list_t *createList(); {  // crea una lista vuota
	// list_t * lista = alloco memoria per un list_t 
	// ritorno lista

}   

int     destroyList(list_t *L){ // libera tutta la memoria allocata dalla lista
	if (L == NULL)
		return -1;

	node_t *head = *L;
	while (head != NULL) {
		if (head->string != NULL)
			free(head->string);
		node_t *tmp = head;
		head = head->next;
		free(tmp);
	}
	free(L);
	return 0;
}


/*
	EFFECTS: libera la memoria occupata dalla stringa e 
	dal nodo della lista che la contiene, per ogni nodo
	MODIFIES: this, testa?
	RETURN: count se la stringa non è allocata correttamente (sring == null),
	dove count è il numero della parola in cui si è interrotta la funzione, 
	0 altrimenti.

*/
int     destroyList(list_t *L){ // libera tutta la memoria allocata dalla lista
	// se L == NULL
	// 	ritorna -1
	// am
	// 	node_t *head = *L
	// 	per ogni elemento head != NULL
	// 		se head->string != NULL
	// 			libero la memoria della stringda
	// 		node_t *tmp = head
	// 		head = head-> next
	// 		libero il nodo tmp

	// 	libero L
	// 	ritorna 0
	if(L == NULL){
		return -1;
	}

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


int insertList(list_t *L, const char * str){
	if(L == NULL){
		return -1;
	}

	note_t * new = (node_t *)malloc(sizeof(node_t));
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
				new->mext = curr;
			}
			return 0;
		}
		prev = curr;
		curr = curr->next;
	}
	prev->next = new;

	return 0;
}
/*
	EFFECTS: crea un nodo contenente la stringa passata 
	e la inserisce in maniera ordinata secondo strcmp dalla testa
	MODIFIES: this, testa pure
	RETURN: 0 se va tutto bene, -1 se la malloc dà errore
*/
int     insertList(list_t *L, const char * str){ // inserisce una parola nella lista
	se L == NULL 
		ritorna -1
	am
		node_t *new = alloco memoria per node_t
		new->next = NULL;
		se str == NULL 
			new->string = NULL
		am
			new->string = alloco memoria per la stringa str
			copio la stringa str in new->string

		node_t *curr = *L
		node_t *prev = NULL
		per ogni curr != NULL
			se curr->string != NULL
				se str < curr->string 
					se prev == NULL
						*L = new
						new->next = curr
						ritorna 0 
					am
						prev->next = new
						new->next = curr
						ritorna 0
				am
					prev = curr
					curr = curr->next 

	se sono arrivata alla fine ho due casi:
	la lista è vuota
	se prev == NULL
		*L = new
	//oppure sono alla fine
	am 
		prev->next = new

	ritorna 0

}

/*
	EFFECTS: stampa ogni stringa della lista
*/
void    printList(list_t *L){ // stampa tutta la lista
	se L == NULL 
		ritorna
	node_t *tmp = *L
	per ogni tmp != NULL
		se il campo string != NULL 
			stampo
		tmp = tmp->next

}
