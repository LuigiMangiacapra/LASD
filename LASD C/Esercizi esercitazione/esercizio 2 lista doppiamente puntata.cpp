/*
Scrivere una funzione ricorsiva in C che accetta una lista doppiamente puntata con caratteri e eliminare tutte le consonanti. 
La lista è rappresentata da una struttura che contiene un campo per il valore e due campi puntatore per il precedente e il successivo elemento della lista.

*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20

struct nodo{
	char info;
	struct nodo* next;
	struct nodo* prev;
};

struct nodo* crea_lista(int size, struct nodo* curr, struct nodo* prec);
void print(struct nodo* lista);
struct nodo* removeConsonants(struct nodo* lista);


int main(){
	
	int size = 0;
	struct nodo* lista = NULL;
	struct nodo* curr = NULL;
	struct nodo* prec = NULL;

	printf("Inserire grandezza della lista\n");
	scanf("%d", &size);
	
	while(size > MAX){
		printf("Inserire massimo %d elementi\n", MAX);
		scanf("%d", &size);
	}
	
	
	lista = crea_lista(size, curr, prec);
	printf("L");
	print(lista);
	printf("\n");
	
	lista = removeConsonants(lista);
	printf("L");
	print(lista);
}


struct nodo* crea_lista(int size, struct nodo* curr, struct nodo* prec){
	char elem[2];
	if(size != 0){
		curr = (struct nodo*)malloc(sizeof(struct nodo*));
		printf("Inserire elemento nella lista\n");
		scanf("%s", &elem[0]);
		curr->info = elem[0];
		curr->next = NULL;
		curr->prev = curr;
		
		size = size - 1;
		curr->next = crea_lista(size, curr->next, prec);
	}
	
}


void print(struct nodo* lista){
	
	if(lista != NULL){
		printf(" -> %c", lista->info);
		print(lista->next);
	}
}




struct nodo* removeConsonants(struct nodo* lista){
	struct nodo* tmp;
	if(lista != NULL){

		lista->next = removeConsonants(lista->next);
		
		if(lista->info != 'a' && lista->info != 'e' && lista->info != 'i' && lista->info != 'o' && lista->info != 'u'){
			tmp = lista;
			lista = lista->next;
			free(tmp);
		}
	}
	return lista;
}



