/*
Aggiugere un nodo che abbia come valore il valore medio della somma di tutti i valori dispari
*/

#include <stdio.h>
#include <stdlib.h>

#define MAX 20
int somma = 0;
int n_elem = 0;

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
struct nodo* calcolo_media(struct nodo* radice);
struct nodo* trova_massimo(struct nodo *radice);


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
	
	radice = calcolo_media(radice);
	media = somma/n_elem;
	radice = inserisci(radice, media);
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


struct nodo* calcolo_media(struct nodo* radice){
	
	if(radice != NULL){
		
		if(radice->inf % 2 != 0){
			somma = somma + radice->inf;
			n_elem = n_elem + 1;
		}
		
		calcolo_media(radice->sinistro);
		calcolo_media(radice->destro);
		
	}
	
	return radice;
}


//stacca l'elemento minimo o lo sostituisce all'elemento eliminato(radice->inf=tmp->inf in elimina_radice)
struct nodo* trova_massimo(struct nodo *radice){
	struct nodo* max = NULL;
	if(radice!=NULL){
		if(radice->destro!=NULL){//naviga l'albero controllando sempre sui figli sinistri, se trova un nodo senza figlio sinistro allora è minimo
			radice=trova_massimo(radice->destro);//Quando bisogna navigare senza modificare non bisogna assegnare a radice->sinistro perché non si modifica nulla
		}												  //trova l'elemento minimo e lo assegna a "radice"
		else{
			max = radice;
		}
	}
	return max;	
}

