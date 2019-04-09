/*OVERVIEW: lista di parole in ordine alfabetico crescente dove in testa ho
 la stringa "più piccola" secondo strcmp
 il valore passato alle funzioni è semre la testa che non deve essere modificata:
 testa ha il campo string a NULL e il primo elemento della lista è puntato da testa->next
*/

/*
	EFFECTS: inizializzo un elemento di tipo list_t* con i parametri nulli:
	string = null
	next = null
	MODIFIES: this, testa
	RETURN: l'elemento creato
*/
list_t *createList(); {  // crea una lista vuota
	malloc spazio per un nodo 
	inizializzo il campo string a null
	inizializzo il campo next a null
	ritorno il nodo
	DONE
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
	se L è NULL ritorna -1
	am
	il puntatore alla testa 'un me serve più' posso scorrere la lista anche con L
	nodo tmp = NULL
	L = l->next
	per ogni elemento L != NULL
	se L->string != NULL, libero la memoria della stringa
	tmp punta a L;
	L = l-> next
	libero il nodo tmp
	ritorna 0
	DONE ?
}               

/*
	EFFECTS: crea un nodo contenente la stringa passata 
	e la inserisce in maniera ordinata secondo strcmp dalla testa
	MODIFIES: this, testa pure
	RETURN: 0 se va tutto bene, -1 se la malloc dà errore
*/
int     insertList(list_t *L, const char * str){ // inserisce una parola nella lista
	se L è NULL ritorna -1
	am
	nuovo nodo inizializzato
	se str == NULL nuovo nodo->string = NULL
	am
	nuovo nodo->string = malloc della dimensione di str
	strncopy della stringa nella lista e str

	nodo current punta L-> next, primo elemento della lista
	nodo prev punta ancora alla testa L
	per ogni current != NULL
	se curr->string != NULL
		se str < curr->string 
			prev->next = nuovo
			nuovo->next = curr
			ritorna 0
	am
	scorro prev
	scorro curr
	se sono arrivata alla fine lo metto alla fine
	prev->next = nuovo nodo
	ritorna 0
	DONE

}

/*
	EFFECTS: stampa ogni stringa della lista
*/
void    printList(list_t *L){ // stampa tutta la lista
	se L è NULL ritorna
	uso un puntatore che punta al successivo della testa tmp= L->next
	per ogni nodo != NULL
	se il campo string != NULL 
	stampo
	scorro tmp
	DONE
}