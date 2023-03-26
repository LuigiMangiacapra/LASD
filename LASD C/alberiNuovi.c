//ALBERI

#include <stdio.h>
#include <stdlib.h>

struct nodo {
	struct nodo * destro;
	struct nodo * sinistro;
	int key;
};

struct nodo * creaNodo(struct nodo * rad, int key);
void printInOrder(struct nodo * rad);
struct nodo * eliminaNodo(struct nodo * rad, int toDelete);
struct nodo * findMin(struct nodo * dx);


int main(){
	
	int numero_nodi, key_value = 0, i = 0, toDelete;
	struct nodo * rad = NULL;
	printf("numero: ");
	scanf("%d", &numero_nodi);
	
	for(i = 0; i < numero_nodi; i++) {
		printf("insert: ");
		scanf("%d", &key_value);
		rad = creaNodo(rad, key_value);
	}
	
	
	printInOrder(rad);
	
	printf("\ntoDelete: ");
	scanf("%d", &toDelete);
	
	rad = eliminaNodo(rad, toDelete);

	printInOrder(rad);
	
	
	return 0;
}


struct nodo * creaNodo(struct nodo * rad, int key) {
	
	if(!rad) {
	 	rad = (struct nodo *)malloc(sizeof(struct nodo));
	 	rad->key = key;
	 	rad->destro = NULL;
	 	rad->sinistro = NULL;
	}
	
	if(key > rad->key) {
		rad->destro = creaNodo(rad->destro, key);
	}
	
	if(key < rad->key) {
		rad->sinistro = creaNodo(rad->sinistro, key);
	}
	

	return rad; 
	
}

void printInOrder(struct nodo * rad) {
	if(!rad) return;
	
	printInOrder(rad->sinistro);
	printf("->%d", rad->key);
	printInOrder(rad->destro);
}


struct nodo * eliminaNodo(struct nodo * rad, int toDelete) {
	if(!rad) return NULL;
 
	else if(toDelete > rad->key) {
		rad->destro = eliminaNodo(rad->destro, toDelete);
	}
	else if(toDelete < rad->key) {
		rad->sinistro = eliminaNodo(rad->sinistro, toDelete);
	}
 
	//abbiamo trovato il nodo da eliminare
	else {
 
		struct nodo * temp;
		if(rad != NULL) {
			if(rad->destro == NULL) {
				temp = rad;
				rad = rad->sinistro;
				free(temp);
			}
 
			else if(rad->sinistro == NULL){
				temp = rad;
				rad = rad->destro;
				free(temp);
			}
 
			else {
 
				// node with two children:
		        // Get the inorder successor
		        // (smallest in the right subtree)
		        struct nodo * temp = findMin(rad->destro);
		        // Copy the inorder
		        // successor's content to this node
		        rad->key = temp->key;
 
		        // Delete the inorder successor
		        rad->destro = eliminaNodo(rad->destro, temp->key);	
		}		
	}
}
 
	return rad;
 
}
 
struct nodo* findMin(struct nodo * node) {
 
    struct nodo* current = node;
 
    /* loop down to find the leftmost leaf */
    while (current && current->sinistro != NULL)
        current = current->sinistro;
 
    return current;
}

