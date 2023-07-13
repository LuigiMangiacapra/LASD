/*
	Scrivere una funzione che, dato un ABR T e un intero x, verifichi che T sia un ABR e restituisca
	la chiave minima del sottoalbero radicato in x
*/


#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct nodo{
	int inf;
	struct nodo *sinistro, *destro;
};


int vuoto(struct nodo* radice){
	if(radice) 
		return 0;
	return 1;
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
	if(!vuoto(radice)){
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

//PROTOTIPI
struct nodo* riconosci_ABR_e_minimo(struct nodo* radice, int x, struct nodo* radice_sub, struct nodo* min, int cont);
struct nodo* inserisci(struct nodo* radice, int k);
void riconosci_ABR_e_minimo_it(struct nodo* radice, int x, struct nodo* radice_sub, struct nodo* min);


int main(){
	struct nodo* radice=NULL;//Mettere sempre NULL
	struct nodo* radice_sub=NULL;
	struct nodo* min=NULL;
	int cont = 0;
	int n,k=0,count=0,scelta,cerca;
	struct elem* p=NULL,*testa=NULL;
	int x = 0;
	
	printf("Quanti elementi vuoi inserire?\n");
	scanf("%d",&n);
	
	while(n){
		count++;
		printf("Inserici elemento %d:\n",count);
		scanf("%d",&k);
		radice=inserisci(radice, k);
		n--;
	}		
	
	printf("Digitare la radice del sottoalbero su cui cercare il minimo\n");
	scanf("%d", &x);
	//riconosci_ABR_e_minimo(radice, x, radice_sub, min, cont);
	riconosci_ABR_e_minimo_it(radice, x, radice_sub, min);
	
}

//inserisce nodo nell'albero 
struct nodo* inserisci(struct nodo* radice, int k){
	
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


struct nodo* riconosci_ABR_e_minimo(struct nodo* radice, int x, struct nodo* radice_sub, struct nodo* min, int cont){
	
	//Scorre ogni nodo dell'albero
	if(radice != NULL){
		
		//Se il figlio destro di un nodo ha un valore maggiore del padre, allora non è un ABR
		if(radice->destro != NULL && radice->destro->inf < radice->inf){
			printf("No\n");
			return radice;
		}
		//Se il figlio sinistro di un nodo ha un valore minore del padre, allora non è un ABR
		else if(radice->sinistro != NULL && radice->sinistro->inf > radice->inf){
			printf("No\n");
			return radice;
		}
		//Se per ora l'albero sembra essere un ABR allora calcoliamo il minimo a partire da una sottoradice
		//printf("node: %d\n", radice->inf);
		
		if(radice->inf == x){//nodo radice su cui trovare il minimo trovato
			
			radice_sub = radice;//radice_sub punta al nodo radice del sottoalbero su cui cercare il minimo
		}
		
		if(radice_sub != NULL){//se radice_sub punta ad un nodo
		
			if(radice_sub == radice){//se radice_sub è stato assegnato come radice del sottoalbero
				
				min = radice_sub->sinistro;//min serve per scorrere sui figli sinistri e trovare il minimo
				
			}
			if(min != NULL){
				
				if(min->sinistro == NULL){//il controllo va fatto prima della chiamata perché altrimenti non viene passato cont agli altri stack di attivazione
					
					cont++;//serve per considerare solo le chiamate ricorsive a sinistra finché non trova il minimo
				}
				
				if(min->sinistro != NULL && cont == 0){//se non è stato trovato il minimo
					
					riconosci_ABR_e_minimo(radice->sinistro, x, radice_sub, min->sinistro, cont);
				}
			}
		}
		
		radice->sinistro = riconosci_ABR_e_minimo(radice->sinistro, x, radice_sub, min, cont);
		
		radice->destro = riconosci_ABR_e_minimo(radice->destro, x, radice_sub, min, cont);
		
		if(min != NULL && cont == 1){
			if(min->sinistro == NULL){
				cont++;
				riconosci_ABR_e_minimo(radice, x, radice_sub, min, cont);//serve per far stampare una sola volta non facendo entrare più nell'if perché cont > 1
				printf("Si, %d\n", min->inf); 
			}
				
		}
			
		
		
	    /* iterativo
		if(radice->inf == x){//nodo radicetrovato
			radice_sub = radice; 
			while(radice_sub->sinistro != NULL){
				radice_sub = radice_sub->sinistro;
			}
			printf("Si, %d\n", radice_sub->inf); 
		}*/
			
	}
	
	return radice;
	
		
}



