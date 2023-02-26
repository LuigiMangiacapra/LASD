/*Creare una lista doppiamente puntata circolare e sostituire ogni elemento pari con la media di tutti gli elementi dispari*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20

struct nodo{
	int inf;
	struct nodo* next, *prev;
};

struct nodo* inserisci_elementi(int n, struct nodo* testa, struct nodo* testa1, struct nodo* testa_lista, struct nodo* ultimo_nodo);
void print_lista(struct nodo* testa, int n);
int funzione_esercizio(struct nodo* testa, int somma, int n, int n_elem);

int main(){
	int n_elem;
	struct nodo* testa = NULL;
	int somma = 0;
	int n = 0, sum=0, num=0;
	printf("Inserire numero di elementi\n");
	scanf("%d", &n_elem);
	
	while(n_elem > 20){
		printf("Inserire max %d elementi\n", MAX);
		scanf("%d", &n_elem);
	}
	
	testa = inserisci_elementi(n_elem, testa, testa, testa, testa);
	printf("L ");
	print_lista(testa, n_elem);
	printf("\n");
	funzione_esercizio(testa, somma, n, n_elem);
	printf("L ");
	print_lista(testa, n_elem);
	
}


struct nodo* inserisci_elementi(int n, struct nodo* testa, struct nodo* testa1, struct nodo* testa_lista, struct nodo* ultimo_nodo){
	
	if(n != 0){
		
		testa=(struct nodo *)malloc(sizeof(struct nodo));//Allocazione di memoria
		printf("inserire primo elemento\n");
		scanf("%d",&testa->inf);
		
		//CREAZIONE SINGOLO NODO
		testa->next = NULL; //da inserire per dare un next iniziale al singolo nodo
		testa->prev = testa1; //per inserire il collegamento al nodo precedente
		testa1 = testa; //aggiornamento del nodo prev
		
		//Punta l'elemento in testa e lo fa puntare da testa_lista
		if(testa->prev == NULL){
			testa_lista = testa;
		}
		
		//se è l'ultimo elemento
		if(n == 1){
			testa->next = testa_lista; //imposta come successivo dell'ultimo nodo il primo nodo della lista
			ultimo_nodo = testa; //utilizziamo un puntatore per puntare all'ultimo elemento che poi servirà durante la risalita
		}
		
		n = n - 1;//Decremento numero di elementi
		testa->next = inserisci_elementi(n, testa->next, testa1, testa_lista, ultimo_nodo);//Chiamata ricorsiva
		
		//Se è il primo elemento
		if(testa->prev == NULL){//se il nodo attuale è quello in testa (unico con testa->prev = NULL)
			testa->prev = ultimo_nodo; //imposta come precedente del nodo in testa, l'ultimo nodo della lista (memorizzato durante la discesa delle chiamate ricorsive)
		}
	}
	
	return(testa);
}



void print_lista(struct nodo* testa, int n){
	
	if(n != 0){
		printf("-> %d ", testa->inf);
		n = n-1;
		print_lista(testa->next, n);
	}
}

int funzione_esercizio(struct nodo* testa, int somma, int n, int n_elem){
	
	if(n_elem == 0){
		return somma / n;
	}
	
	//somma e conta tutti i valori dispari
	if(testa->inf % 2 != 0){
		somma = somma + testa->inf;
		n++;
		printf("somma: %d, n: %d\n", somma, n);
		n_elem = n_elem - 1;
	}
	else{ //se il valore è pari viene sostituito
		n_elem = n_elem - 1;
		testa->inf = funzione_esercizio(testa->next, somma, n, n_elem);
	}	
	
	return funzione_esercizio(testa->next, somma, n, n_elem);
}



