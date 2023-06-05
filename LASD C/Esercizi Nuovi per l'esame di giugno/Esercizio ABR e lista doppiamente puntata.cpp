/*
Creare una lista doppiamente puntata non circolare e un albero ternario, controllare se il figlio centrale ha come valore la media o la media per difetto dei suoi fratelli,
se fosse così aggiungere l'elemento nella lista doppiamente puntata.
*/

#include <stdio.h>
#include <stdlib.h>

struct nodo{
	int inf;
	struct nodo* next;
	struct nodo* prev;
};

struct tree{
	int inf;
	struct tree* destro;
	struct tree* centro;
	struct tree* sinistro;
};

struct nodo* inserisci_lista(int n_elem);
void stampa_lista(struct nodo* L);
struct tree* inserisci_nodo(struct tree* T, int elem);
void stampa_albero(struct tree* T);
struct nodo* funzione_esercizio(struct nodo* L, struct tree* T);

int main(){
	int n_elem, n_elem_albero;
	struct nodo* L = NULL;
	struct tree* T = NULL;
	int i = 0;
	int elem = 0;
	
	//INSERIMENTO LISTA
	printf("Inserimento lista\n");
	printf("Inserisce numero di elementi della lista\n");
	scanf("%d", &n_elem);
	L = inserisci_lista(n_elem);
	stampa_lista(L);
	
	
	//INSERIMENTO ALBERO
	printf("Inserimento albero\n");
	printf("Inserisce numero di elementi dell' albero'\n");
	scanf("%d", &n_elem_albero);
	while(i < n_elem_albero){
		printf("Inserire %d° elemento: ",i+1);
		scanf("%d", &elem);
		T = inserisci_nodo(T, elem);
		i++;
	}
	stampa_albero(T);

	printf("\n\n");
	//FUNZIONE ESERCIZIO
	L = funzione_esercizio(L, T);
	
	printf("Lista: \n");
	stampa_lista(L);
	
	printf("\n\n");
	
	printf("Albero: \n");
	stampa_albero(T);
	
}


struct nodo* inserisci_lista(int n_elem){
	struct nodo* L, *punt;
	int i = 0;
	L = (struct nodo*)malloc(sizeof(struct nodo));
	if(L == NULL){
		perror("Allocazione non possibile");
		exit(1);
	}
	else{
        printf("\nInserisci il primo valore: ");
        scanf("%d", &L->inf);
        punt = L;
        
        for(i = 1; i < n_elem; i++){
        	punt->next = (struct nodo*)malloc(sizeof(struct nodo));
        	punt->next->prev = punt;
        	punt = punt->next;
        	printf("Inserisci il %d° valore: ", i);
        	scanf("%d", &punt->inf);
		}
		punt->next = NULL;
        
	}
	
	
	return L;
}



void stampa_lista(struct nodo* L){
	if(L != NULL){
		printf("%d -> ", L->inf);
		stampa_lista(L->next);
	}
	else{
		printf("NULL\n");
		return;
	}
	
}


struct tree* inserisci_nodo(struct tree* T, int elem){
	if (T == NULL) {
        struct tree* new_nodo = (struct tree*)malloc(sizeof(struct tree));
        if (new_nodo == NULL) {
            perror("Allocazione non possibile");
            exit(1);
        }
        new_nodo->inf = elem;
        new_nodo->sinistro = NULL;
        new_nodo->centro = NULL;
        new_nodo->destro = NULL;
        return new_nodo;
    }

    if (T->inf < elem) {
        T->destro = inserisci_nodo(T->destro, elem);
    } 
	else if (T->inf > elem) {
        T->sinistro = inserisci_nodo(T->sinistro, elem);
    } 
	else if (T->sinistro != NULL && T->destro != NULL && T->sinistro->inf < elem && T->destro->inf > elem) {
        T->centro = inserisci_nodo(T->centro, elem);
    }

    return T;
}

void stampa_albero(struct tree* T){
	
	if(T != NULL){
		stampa_albero(T->sinistro);
		printf(" |%d| ",T->inf);
		stampa_albero(T->centro);
		stampa_albero(T->destro);
	}
	
}


struct nodo* funzione_esercizio(struct nodo* L, struct tree* T){
	if(T != NULL){
		if(T->centro != NULL && T->sinistro != NULL && T->destro != NULL && (T->centro->inf == ((T->sinistro->inf + T->destro->inf)/2))){
			struct nodo* new_elem = (struct nodo*)malloc(sizeof(struct nodo));
			new_elem->inf = T->centro->inf;
			new_elem->next = L;
			L = new_elem;
		}
		funzione_esercizio(L, T->sinistro);
		funzione_esercizio(L, T->centro);
		funzione_esercizio(L, T->destro);
	}
	return L;
}
