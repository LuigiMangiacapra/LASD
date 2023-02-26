/*
Scrivere una funzione che, dato un ABR T, verifichi che T sia un ABR e costruisca un albero T'
ternario in modo che, per ogni nodo in T che abbia entrambi i figli, si aggiunge in T' un terzo
figlio middle, che è un nodo foglia, contenente la somma delle chiavi dei due fratelli.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct nodo{
	int inf;
	struct nodo *sinistro, *middle, *destro;
};


int vuoto(struct nodo* radice){
	if(radice) return 0;
	return 1;
}


struct nodo* crea_nodo(struct nodo* sinistro, struct nodo* destro, int elem){
	struct nodo* padre;
	padre=(struct nodo*)malloc(sizeof(struct nodo));
	if(padre){
		padre->inf=elem;
		padre->destro=destro;
		padre->sinistro=sinistro;
	}
	return padre;
}


struct nodo* inserisci(struct nodo* radice, int k);
void stampa_in_ordine(struct nodo*radice);
struct nodo* crea_albero_ternario(struct nodo* radice);
struct nodo* somma_fratelli(struct nodo* radice);


int main(){
	struct nodo* radice=NULL;
	struct nodo* radice2=NULL;
	int n,k,count=0;
	
	printf("Quanti elementi vuoi inserire?\n");
	scanf("%d",&n);
	
	while(n){
		count++;
		printf("Inserici elemento %d:\n",count);
		scanf("%d",&k);
		radice = inserisci(radice, k);
		n--;
	}
	
	stampa_in_ordine(radice);
	
	printf("\nAlbero ternario\n");
	//radice2 = crea_albero_ternario(radice);
	radice2 = somma_fratelli(radice);
	stampa_in_ordine(radice2);
}


//inserisce nodo nell'albero 
struct nodo* inserisci(struct nodo* radice, int k){
	
	//Se non ci sono elementi, il nodo viene creato e inserito coem radice
	if(radice==NULL)
		radice=crea_nodo(NULL, NULL,k);//Ricordare sempre il tipo di ritorno di una funzione che modifica la struttura
	else{
		if(radice->inf<k)
			radice->destro=inserisci(radice->destro,k);
		else if(radice->inf>k)
			radice->sinistro=inserisci(radice->sinistro,k);
	}
	return radice;
}


//stampa l'albero in ordine
void stampa_in_ordine(struct nodo* radice){
	if(radice!=NULL){
		printf(" |%d| ",radice->inf);
		stampa_in_ordine(radice->sinistro);
		stampa_in_ordine(radice->middle);
		stampa_in_ordine(radice->destro);
		
	}
			
}


/*//Inserisce tutti i nodi dell'albero di partenza in un nuovo albero ternario
struct nodo* crea_albero_ternario(struct nodo* radice){
	struct nodo* radice2=NULL;
	
	if(radice != NULL){
		
		radice2 = inserisci(radice2, radice->inf); //Inserisce il valore del nodo radice dell'albero di partenza, nel nuovo albero. Sarà ritornato l'albero modificato
		
		//Chiamate ricorsive che aggiornano la radice, i nuovi nodi saranno i figli del nodo attuale
		//Quando c'è la risalità si risalirà sull'albero che si sta creando attraverso la funzione inserisci, che inserisce ogni nodo a seconda del proprio valore
		radice2->sinistro = crea_albero_ternario(radice->sinistro); 
		radice2->destro = crea_albero_ternario(radice->destro);
	}
	

	return radice2;
	
}*/


struct nodo* somma_fratelli(struct nodo* radice){
	int somma = 0;
	struct nodo* radice2=NULL;
	struct nodo* curr = radice;
	
	//INSERIMENTO DI TUTTI GLI ELEMENTI DEL PRIMO ALBERO NEL SECONDO
	if(radice != NULL){
		if(radice->sinistro != NULL && radice->sinistro->inf > radice->inf){ //se il nodo corrente ha un figlio sinistro e il figlio sinistro ha un valore maggiore del padre allora non è un ABR
			printf("l'albero T non è un ABR\n");
			return radice;
		}
		if(radice->destro != NULL && radice->destro->inf < radice->inf){ //se il nodo corrente ha un figlio destro e il figlio destro ha un valore minore del padre allora non è un ABR
			printf("l'albero T non è un ABR\n");
			return radice;
		}
		radice2 = inserisci(radice2, radice->inf);//Inserisce tutti gli elementi dell'albero iniziale in un nuovo albero
		
		//Ricerca del nodo con due figli attraverso chiamate ricorsive
		radice2->sinistro = somma_fratelli(radice->sinistro);
		radice2->destro = somma_fratelli(radice->destro);
		
		
		//INSERIMENTO DEL TERZO ELEMENTO DI MEZZO CON VALORE SOMMA DEL FIGLIO DESTRO E SINISTRO
		//Assicurarsi che il nodo corrente abbia entrambi i figli
		if(radice2->sinistro != NULL && radice2->destro != NULL){
			
			//Calcolo della somma dei due fratelli
			somma = radice2->sinistro->inf + radice2->destro->inf;
			//Creazione del nodo con valore "somma" e successivamente puntato da radice->middle
			radice2->middle = crea_nodo(NULL, NULL, somma);
		}
	}
	return radice2;
}
