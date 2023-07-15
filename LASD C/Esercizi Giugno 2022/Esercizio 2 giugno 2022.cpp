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
int riconosci_ABR_e_minimo2(struct nodo** radice, int x, struct nodo** radice_sub, int is_bst, int min, int count);
void stampa_albero(struct nodo* radice);


int main(){
	struct nodo* radice=NULL;//Mettere sempre NULL
	struct nodo* radice_sub=NULL;
	//struct nodo* min=NULL;
	int min = 0;
	int cont = 0;
	int n,k=0,count=0,scelta,cerca;
	struct elem* p=NULL,*testa=NULL;
	int x = 0;
	int is_bst = 0;
	int count2 = 0;
	
	printf("Quanti elementi vuoi inserire?\n");
	scanf("%d",&n);
	
	while(n){
		count++;
		printf("Inserici elemento %d:\n",count);
		scanf("%d",&k);
		radice=inserisci(radice, k);
		n--;
	}
	
	printf("Stampa albero\n");		
	stampa_albero(radice);
	
	
	printf("\nDigitare la radice del sottoalbero su cui cercare il minimo\n");
	scanf("%d", &x);
	//riconosci_ABR_e_minimo(radice, x, radice_sub, min, cont);
	//riconosci_ABR_e_minimo_it(radice, x, radice_sub, min);
	
	radice_sub = radice;
	min = riconosci_ABR_e_minimo2(&radice, x, &radice_sub, is_bst, min, count2);
	
	printf("L'albero e' un ABR e il minimo del sottoalbero radicato in %d e': %d\n", x, min);
	
	printf("Stampa albero dopo modifiche\n");		
	stampa_albero(radice);
	printf("\nIl valore minimo %d e' stato eliminato\n", min);
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


void stampa_albero(struct nodo* radice){
	if(radice != NULL){
		stampa_albero(radice->sinistro);
		printf("|%d| ", radice->inf);
		stampa_albero(radice->destro);
	}
}


int riconosci_ABR_e_minimo2(struct nodo** radice, int x, struct nodo** radice_sub, int is_bst, int min, int count) {
	struct nodo* tmp;
	if (*radice == NULL || *radice_sub == NULL) {
		is_bst = 1;
		return min;
	}

	if ((*radice)->destro != NULL && (*radice)->destro->inf < (*radice)->inf) {
		printf("L'albero non è un ABR\n");
		return min;
	}

	else if ((*radice)->sinistro != NULL && (*radice)->sinistro->inf > (*radice)->inf) {
		printf("L'albero non è un ABR\n");
		return min;
	}

	if ((*radice)->inf == x) {
		*radice_sub = *radice;
		count++;
	}

	min = riconosci_ABR_e_minimo2(&((*radice)->sinistro), x, &((*radice_sub)->sinistro), is_bst, min, count);

	min = riconosci_ABR_e_minimo2(&((*radice)->destro), x, radice_sub, is_bst, min, count);

	if ((*radice_sub)->sinistro == NULL && (*radice_sub)->destro == NULL && count == 1) {
		min = (*radice_sub)->inf;
		free(*radice_sub);  // Elimina l'elemento quando entrambi i figli sono NULL
		*radice_sub = NULL;  // Imposta il puntatore del nodo eliminato a NULL
		
	}
	return min;
}




