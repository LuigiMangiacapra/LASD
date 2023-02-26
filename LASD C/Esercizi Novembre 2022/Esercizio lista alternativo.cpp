/*
Data una lista doppiamente puntata e cricolare, scrivere una funzione che rimpiazzi ogni elemento pari
con la somma degli elementi alla sua destra e alla sua sinistra.
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20

struct elem{
	int info;
	struct elem* next;
	struct elem* prev;
};

struct elem* crea_lista(int n_elem, struct elem* prec, struct elem* curr);
void print_lista(struct elem* testa);
int somma_elem(struct elem* testa, int somma);
struct elem* substitute_even(int n_elem, struct elem* testa, int somma);
struct elem* replaceEven(struct elem *current, struct elem *head);



int main(){
	int n_elem;
	struct elem* lista = NULL;
	struct elem* prec = NULL, *curr = NULL;
	printf("Digitare quanti elementi inserire nella lista\n");
	scanf("%d", &n_elem);
	
	while(n_elem > MAX){
		printf("Digitare max %d elementi\n", MAX);
		scanf("%d", &n_elem);
	}
	
	lista = crea_lista(n_elem, prec, curr);
	
	print_lista(lista);
	
	printf("\n");
	
	lista = replaceEven(lista, lista);

	
	print_lista(lista);
}


struct elem* crea_lista(int n_elem, struct elem* prec, struct elem* curr){
	int elem;
	struct elem* testa = NULL;
	
	if(n_elem != 0){
		curr = (struct elem*)malloc(sizeof(struct elem));
		if (curr == NULL) {
   			printf("Errore: impossibile allocare memoria.\n");
    		exit(1);
		}	
		printf("Inserire elemento\n");
		scanf("%d", &elem);
		curr->info = elem;
		curr->next = NULL;
		curr->prev = NULL;
		
		if(prec != NULL){
			prec->next = curr;
			curr->prev = prec;
		}
		else
			testa = curr;
		
		if(n_elem == 1){
			curr->next = testa;
			testa->prev = curr;
		}
		
		n_elem = n_elem - 1;
		curr->next = crea_lista(n_elem, prec, curr->next);
	}
	
	return testa;
}



void print_lista(struct elem* testa){
	
	if(testa != NULL){
		
		printf("|%d| ", testa->info);
		print_lista(testa->next);
	}
}


// funzione ricorsiva per il rimpiazzo degli elementi pari
struct elem* replaceEven(struct elem *current, struct elem *head) {
    if (current == NULL || current->next == head) return NULL;

    if (current->info % 2 == 0) {
        int sum = current->prev->info + current->next->info;
        current->info = sum;
    }

    replaceEven(current->next, head);
    
    return head;
}


