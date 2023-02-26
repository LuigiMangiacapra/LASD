/*
Scrivere una funzione che, dato un ABR T e una chiave k, verifichi che T sia un ABR e che k sia in T. Poi si rimuove il minimo del sottoalbero radicato in T.
*/
#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

struct nodo{
	int inf;
	struct nodo *sinistro, *destro;
};

struct nodo* crea_nodo(struct nodo* sinistro, struct nodo* destro, int elem){
	struct nodo* nuovo;
	nuovo = (struct nodo*)malloc(sizeof(struct nodo));
	
	if(nuovo != NULL){
		nuovo->inf = elem;
		nuovo->destro = destro;
		nuovo->sinistro = sinistro;
	}
	return nuovo;
}

struct nodo *crea_albero(struct nodo* T, int elem);
void stampa(struct nodo* T);
void funzione_esercizio(struct nodo* T, int k);
struct nodo* trova_elemento(struct nodo* T, int k);
struct nodo* elimina_minimo(struct nodo* T);
int isBST(struct nodo* root);


int main(){
	int n_elem, elem, k;
	struct nodo* T = NULL; //Mettere T = NULL sempreeeeeeee!
	printf("Quanti elementi vuoi inserire?\n");
	scanf("%d", &n_elem);
	
	while(n_elem != 0){
		printf("Inserire elemento\n");
		scanf("%d", &elem);
		T = crea_albero(T, elem);
		n_elem--;
	}
	
	stampa(T);
	printf("\nInserire valore da trovare\n");
	scanf("%d", &k);
	funzione_esercizio(T, k);
	printf("\n");
	stampa(T);
}


void stampa(struct nodo* T){
	if(T != NULL){
		stampa(T->sinistro);
		printf("|%d| ", T->inf);
		stampa(T->destro);
	}
}


struct nodo* crea_albero(struct nodo* T, int elem){
	
	if(T == NULL){
		T = crea_nodo(NULL, NULL, elem);
	}
	else{
		if(elem > T->inf)
			T->destro = crea_albero(T->destro, elem);
		else if(elem < T->inf)
			T->sinistro = crea_albero(T->sinistro, elem);	
		
	}
	return T;
}


void funzione_esercizio(struct nodo* T, int k){
	int flag = 1;	
	
	flag = isBST(T);
	
	if(flag == 0)
		printf("L'albero non e' un ABR");
	else{
		T = trova_elemento(T, k);
		if(T->inf == k){
			printf("L'albero e' un ABR e il valore %d e' presente", k);
			
			if(T->sinistro != NULL)
				T = elimina_minimo(T);
			
		}
		else
			printf("L'albero e' un ABR e il valore %d non e' presente", k);
	}
	
}


int isBST(struct nodo* root) {
    if (root == NULL) {
        return 1;
    }
    if (root->sinistro != NULL && root->sinistro->inf > root->inf) {
        return 0;
    }
    if (root->destro != NULL && root->destro->inf < root->inf) {
        return 0;
    }
    if (!isBST(root->sinistro) || !isBST(root->destro)) {
        return 0;
    }
    return 1;
}


struct nodo* trova_elemento(struct nodo* T, int k){
	int trovato = 0;
	if(T != NULL){
		if(T->inf == k){
			return T;
		}
		else{

			if(T->inf < k){
				T = trova_elemento(T->destro, k);
			}
			else if(T->inf > k){
				T = trova_elemento(T->sinistro, k);
			}
		}
	}
	return T;
}

//problema quando il nodo T trovato non ha figlo sinistro senza quindi effettuare la chiamata ricorsiva
struct nodo* elimina_minimo(struct nodo* T){
	struct nodo* tmp;
	if(T != NULL){
		if(T->sinistro != NULL){
			T->sinistro = elimina_minimo(T->sinistro);
		}
		else{
			tmp = T;
			T = T->destro; //CAMBIA RIFERIMENTO PRIMA DELL'ELIMINAZIONE E FA PUNTARE L'ELEMENTO PRECEDENTE AL NUOVO FIGLIO SINISTRO PRIMA DI ELIMINARLO
			free(tmp);	
			
		}
	}
	return T;
}
