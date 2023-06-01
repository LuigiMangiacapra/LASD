/*
Scrivere una funzione in linguaggio C che preso in input 
un albero binario con n elementi valuti in tempo O(n) 
se l albero è un ABR.
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

//STRUTTURA
struct nodo{
	int inf;
	struct nodo *sinistro, *destro;	
};

int vuoto(struct nodo* radice){
	if(radice) 
		return 0; //l'albero non è vuoto se radice != NULL
	return 1; //l'albero è vuoto poiché radice = NULL
}

int radice(struct nodo* radice, struct nodo *val){
	int ok=0;
	if(!vuoto(radice)){
		val->inf=radice->inf;
		ok=1;
	}
	return ok;
}

struct nodo* sinistro(struct nodo* radice){
	struct nodo*sinistro=NULL;
	if(!vuoto(radice)){ //se l'albero non è vuoto, perché altrimenti non ci sarebbero figli, inizializziamo la variabile sinistro con il figlio sinistro del nodo dato in input
		sinistro=radice->sinistro;
	}
	return sinistro;
}

struct nodo* destro(struct nodo* radice){
	struct nodo*destro=NULL;
	if(!vuoto(radice)){
		destro=radice->sinistro;
	}
	return destro;
}

struct nodo* crea_nodo(struct nodo* sinistro, struct nodo* destro, int elem){ //per creare un nodo abbiamo bisogno di puntatori sul figlio destro e sinistro e il valore per il nodo da creare
	struct nodo* padre;
	padre=(struct nodo*)malloc(sizeof(struct nodo)); //crea spazio in memoria per il nodo da creare
	if(padre != NULL){ //se lo spazio è stato allocato con successo, perché altrimenti sarebbe rimasto = NULL
		padre->inf=elem; //assegna il valore dato in input
		padre->destro=destro; //lega il puntatore destro al figlio destro del nodo creato
		padre->sinistro=sinistro;
	}
	return padre;
}


//PROTOTIPI
int riconosci_ABR(struct nodo* radice);
struct nodo* inserisci(struct nodo* radice, int k);
int inserisciMaxMin(struct nodo* node, int min, int max);


int main(){
	struct nodo* radice;
	int n,k,count=0;
	
	printf("Quanti elementi vuoi inserire?\n");
	scanf("%d",&n);
	
	while(n){
		count++;
		printf("Inserici %d elemento:\n",count);
		scanf("%d",&k);
		inserisci(radice, k); //inserisce un nodo con valore k in un albero con radice "radice"
		n--;
	}
	
	if(riconosci_ABR(radice))
		printf("\nE' un ABR\n");
	else
		printf("\nNon e'' un ABR\n");
}


struct nodo* inserisci(struct nodo* radice, int k){
	
	if(radice==NULL)
		crea_nodo(NULL, NULL,k); //crea il nodo se l'albero non ha elementi o se ci si trova in un figlio di una foglia (NULL) e gli dà come figli dei nodi NULL perché il nodo sarà una foglia
	else{
		if(radice->inf<k) //se k è più grande del valore del nodo corrente l'inserimento va fatto sul sottoalbero destro del nodo corrente
			radice->destro=inserisci(radice->destro,k);
		else if(radice->inf>k)
			radice->sinistro=inserisci(radice->sinistro,k);
	}
	return radice;
}


//UN ALBERO E' UN ABR SE E SOLO SE HA L'ELEMENTO MINIMO IN FONDO A SINISTRA E L'ELEMENTO MASSIMO IN FONDO A DESTRA

//VERSIONE EFFICIENTE
/*int riconosci_ABR(struct nodo* radice){
	return (inserisciMaxMin(radice, INT_MIN, INT_MAX));//INT_MIN e INT_MAX sono costanti che rappresentano il minimo e massimo valore intero rappresentabile
}

int inserisciMaxMin(struct nodo* node, int min, int max){
	
	//un albero vuoto è un ABR
	if(node==NULL)
		return 1;
		
	//falso se questo nodo vìola il vincolo min/max
	if(node->inf < min || node->inf >max)//se trova un elemento minore del minimo o maggiore del massimo non è un ABR
		return 0;
	
	//altrimenti controlla i sottoalberi ricorsivamente, 
	stringendo il vincolo massimo o il vincolo minimo
	return(inserisciMaxMin(node->sinistro, min, node->inf-1) && inserisciMaxMin(node->destro, node->inf+1, max));
	//node->inf viene decrementato nella prima chiamata affinché si trovi un elemento che sia minore di min, se non lo si trova bene, allora è un ABR
	//________________incrementato_______seconda______________________________________________maggiore di max________________________________________
}
*/


//VERSIONE POCO EFFICIENTE MA PIU' INTUIBILE
int riconosci_ABR(struct nodo* radice){
	
	if(radice == NULL)
		return 1;
		
	if(radice->sinistro != NULL && radice->sinistro->inf > radice->inf) //se il nodo corrente ha un figlio sinistro e il figlio sinistro ha un valore maggiore del padre allora non è un ABR
		return 0;
		
	if(radice->destro != NULL && radice->destro->inf < radice->inf) //se il nodo corrente ha un figlio destro e il figlio destro ha un valore minore del padre allora non è un ABR
		return 0;
		
	if(!riconosci_ABR(radice->sinistro) || !riconosci_ABR(radice->destro)) //questo if contiene le chiamate ricorsive e il ritorno di entrambi sarà confrontato nell'if 
		return 0;
		
	return 1;
}


