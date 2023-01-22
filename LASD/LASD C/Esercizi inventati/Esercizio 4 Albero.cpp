/*
	Aggiungere ad ogni foglia un figlio che abbia il valore della foglia + 1
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20

struct nodo{
	int inf;
	struct nodo* sinistro, *destro;
};


//Macro
struct nodo* crea_nodo(struct nodo* sinistro, struct nodo* destro, int elem){
	struct nodo* nuovo = NULL;
	nuovo = (struct nodo*)malloc(sizeof(struct nodo));
	
	if(nuovo != NULL){
		nuovo->inf = elem;
		nuovo->sinistro = sinistro;
		nuovo->destro = destro;
	}
	return nuovo;
}


struct nodo* inserisci(struct nodo* radice, int elem);
void stampa_in_ordine(struct nodo* radice);
struct nodo* crea_figli_foglie(struct nodo* radice);

int main(){
	
	int n = 0, elem = 0, media = 0, count = 0;
	struct nodo* radice = NULL;
	
	printf("Inserire il numero di elementi da inserire\n");
	scanf("%d", &n);
	
	while(n){
		count++;
		printf("Inserici elemento %d:\n",count);
		scanf("%d",&elem);
		radice=inserisci(radice, elem);
		n--;
	}

	radice =  crea_figli_foglie(radice);
	stampa_in_ordine(radice);
}



struct nodo* inserisci(struct nodo* radice, int elem){
	
	if(radice == NULL){
		radice = crea_nodo(NULL, NULL, elem);
	}
	else{
		if(elem > radice->inf){
			radice->destro = inserisci(radice->destro, elem);
		}
		else if (elem < radice->inf){
			radice->sinistro = inserisci(radice->sinistro, elem);
		}
	}
	
	return radice;
}


//stampa l'albero in ordine
void stampa_in_ordine(struct nodo* radice){
	if(radice!=NULL){
		stampa_in_ordine(radice->sinistro);
		printf(" |%d| ",radice->inf);
		stampa_in_ordine(radice->destro);
		
	}
			
}


struct nodo* crea_figli_foglie(struct nodo* radice){
	
	if(radice != NULL){
		if(radice->destro != NULL || radice->sinistro != NULL){
			if(radice->destro != NULL)
				radice->destro = crea_figli_foglie(radice->destro);
			if(radice->sinistro != NULL)
				radice->sinistro = crea_figli_foglie(radice->sinistro);
		}
		else{
			radice->destro = crea_nodo(NULL, NULL, radice->inf + 1);
		}
		
		
	}
	
	return radice;
}


