/*Creare una funzione che verifichi che l'albero è un ABR, che trova il minimo del sottoalbero radicato in k lo elimini e stampi alla fine "L'albero è un ABR e il minimo k è stato eliminato"*/

#include <stdio.h>
#include <stdlib.h>

struct tree{
	int key;
	struct tree* sinistro;
	struct  tree* destro;
};


struct tree* inserire_nodo(struct tree* T, int elem);
void stampa_albero(struct tree* T);
void esercizio (struct tree* T, struct tree* radice_sub, int k);

int main(){
	int size;
	int i = 0, elem;
	struct tree* T = NULL, *radice_sub = NULL;
	int k;
	
	printf("Digita quanti elementi vuoi inserire\n");
	scanf("%d", &size);
	
	while(i < size){
		printf("Inserire elemento\n");
		scanf("%d", &elem);
		T = inserire_nodo(T, elem);
		i++;
	}
	
	
	stampa_albero(T);
	
	radice_sub = T;
	printf("\nInserire la radice k\n");
	scanf("%d", &k);
	
	esercizio (T, radice_sub, k);
}


struct tree* inserire_nodo(struct tree* T, int elem){
	struct tree* new_elem;
	if(T == NULL){
		new_elem = (struct tree*)malloc(sizeof(struct tree));
		new_elem->key = elem;
		new_elem->sinistro = NULL;
		new_elem->destro = NULL;
		return new_elem;
	}
	else{
		if(elem < T->key)
			T->sinistro = inserire_nodo(T->sinistro, elem);
		if(elem > T->key)
			T->destro = inserire_nodo(T->destro, elem);
	}
	return T;
}


void stampa_albero(struct tree* T){
	
	if(T != NULL){
		stampa_albero(T->sinistro);
		printf("|%d| ", T->key);
		stampa_albero(T->destro);
	}
		
}

void esercizio (struct tree* T, struct tree* radice_sub, int k){
	
	if(T == NULL){
		return;
	}
	
	if(T->sinistro != NULL && T->sinistro->key > T->key){
		printf("L'albero non è un ABR\n");
		return;
	}
	else if(T->destro != NULL && T->destro->key < T->key){
		printf("L'albero non è un ABR\n");
		return;
	}
	
	if(T->key == k){
		radice_sub = T;
	}
	
	if(radice_sub->sinistro == NULL){
		printf("L'albero e' un ABR e il minimo e' %d\n", radice_sub->key);
		return;
	}
	
	esercizio(T->sinistro, radice_sub->sinistro, k);
	esercizio(T->destro, radice_sub, k);

}


