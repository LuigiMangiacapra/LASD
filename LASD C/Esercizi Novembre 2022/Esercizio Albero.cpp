/* 
	Dato un albero e due chiavi k1 e k2, scrivere una funzione che verifichi che l'albero
	sia binario di ricerca e verifichi che il massimo del sottoalbero radicato in k1 sia multiplo
	di k2
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20

struct nodo{
	int info;
	struct nodo* destro;
	struct nodo* sinistro;
};


struct nodo* crea_nodo(struct nodo* sinistro, struct nodo* destro, int elem){
	struct nodo* nuovo = (struct nodo*)malloc(sizeof(struct nodo));
	if(nuovo != NULL){
		nuovo->info = elem;
		nuovo->sinistro = sinistro;
		nuovo->destro = destro;
	}
	return nuovo;
}

struct nodo* crea_albero(struct nodo* radice, int elem);
void stampa_albero(struct nodo* radice);
int is_bst(struct nodo* radice);
struct nodo* find_max(struct nodo* radice);
void merge_func(struct nodo* radice);
struct nodo* find_rad(struct nodo* radice, int elem);

int main(){
	int n_elem, elem;
	int i = 0;
	struct nodo* radice = NULL;
	printf("Digitare grandezza albero\n");
	scanf("%d", &n_elem);
	
	while(n_elem > MAX){
		printf("Inserire max %d elementi\n", MAX);
		scanf("%d", &n_elem);
	}
	
	while(i < n_elem){
		printf("Inserire elemento\n");
		scanf("%d", &elem);
		radice = crea_albero(radice, elem);
		i++;
	}
	
	stampa_albero(radice);
	printf("\n");
	merge_func(radice);
	
}


struct nodo* crea_albero(struct nodo* radice, int elem){
	
	if(radice == NULL){
		radice = crea_nodo(NULL, NULL, elem);
	}
	else{
		if(elem > radice->info){
			radice->destro = crea_albero(radice->destro, elem);
		}
		if(elem < radice->info){
			radice->sinistro = crea_albero(radice->sinistro, elem);
		}
	}
	
	return radice;
}



void stampa_albero(struct nodo* radice){
	if(radice != NULL){
		stampa_albero(radice->sinistro);
		printf("|%d| ", radice->info);
		stampa_albero(radice->destro);
	}
}


struct nodo* find_rad(struct nodo* radice, int elem){
	
	if(radice != NULL){
		if(radice->info == elem){
			return radice;
		}
		else{
			
			if(radice->info < elem){
				radice = find_rad(radice->destro, elem);
			}
			else if(radice->info > elem){
				radice = find_rad(radice->sinistro, elem);
			}
	
		}
	
	}
	return radice;
}


int is_bst(struct nodo* root){

	if (root == NULL) {
        return 1;
    }
    if (root->sinistro != NULL && root->sinistro->info > root->info) {
        return 0;
    }
    if (root->destro != NULL && root->destro->info < root->info) {
        return 0;
    }
    if (is_bst(root->sinistro) == 0 || is_bst(root->destro) == 0) { //Appena si risale dalla prima chiamata ricorsiva e il nodo corrente ha il figlio destro, effettua la seconda chiamata
        return 0;
    }

    return 1;
}


struct nodo* find_max(struct nodo* radice){
	
	if(radice != NULL){
		printf("radice-dis: %d\n", radice->info);
		if(radice->destro != NULL){
			
			radice = find_max(radice->destro);//Radice viene riempito con l'ultimo elemento perché lo stack che contiene tale elemento non effettua chiamate ricorsive e ritorna l'elemento.
											  //Dopodiché le altre chiamate non ritornano elementi, quindi radice rimane con il medesimo elemento
			
		}
		printf("radice-ris: %d\n", radice->info);
	}
	return radice;
}


void merge_func(struct nodo* radice){
	
	int elem; 
	struct nodo* max = NULL;
	struct nodo* rad = NULL;
	
	int flag = is_bst(radice);
	
	if(flag == 0){
		printf("L'albero non e' un ABR\n'");
		return;
	}
	else{ 
		printf("Digitare radice del sottoalbero\n");
		scanf("%d", &elem);
		
		rad = find_rad(radice, elem);
		
		if(rad == NULL){
        	printf("La radice del sottoalbero non e' presente nell'albero\n");
        	return;
    	}
			
		max = find_max(rad);
		
		if(max->info % rad->info == 0){
			printf("L'albero e' un ABR e %d e' multiplo di %d", max->info, rad->info);
		
		}
		else{
			printf("L'albero e' un ABR e %d non e' multiplo di %d", max->info, rad->info);
			
		}
	}
}

