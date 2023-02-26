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

struct elem* crea_lista(int n_elem);
void print_lista(struct elem* testa, int n);
struct elem* replaceEven(struct elem *current, struct elem *head);



int main(){
	int n_elem;
	struct elem* lista = NULL;
	struct elem* prec = NULL, *curr = NULL;
	
	printf("\n Specificare il numero di elementi... ");
	scanf("%d", &n_elem);
	
	lista = crea_lista(n_elem);
	
	print_lista(lista, n_elem);
	
	printf("\n");
	
	lista = replaceEven(lista, lista);

	print_lista(lista, n_elem);
	
}


struct elem *crea_lista(int n) {
	struct elem *p, *punt;
	int i;
	if(n==0) 
		p = NULL; 
	else {
		/* creazione elemento in testa */
		p = (struct elem *)malloc(sizeof(struct elem));
		printf("\nInserisci il primo valore: ");
		scanf("%d", &p->info);
		punt = p;
		
		for(i=1; i < n; i++){
			punt->next = (struct elem *)malloc(sizeof(struct elem)); //alloca memoria dell'elemento successivo
			punt->next->prev=punt; //imposta il nodo attuale come precedente del succesivo
			punt = punt->next; //cambia puntatore al nodo successivo
			printf("\nInserisci il %d elemento: ", i);
			scanf("%d", &punt->info);
		} // chiudo il for
		punt->next = p; 
		p->prev = punt; // circolarità della lista
	} // chiudo l'if-else
	return(p);
} // chiudo la funzione

struct elem* crea_lista(int n_elem, struct elem* prec, struct elem* curr, struct elem* testa){
	int elem;
	
	if(n_elem != 0){
		
		if(testa == NULL){
			testa = (struct elem*)malloc(sizeof(struct elem));
			if (testa == NULL) {
	   			printf("Errore: impossibile allocare memoria.\n");
	    		exit(1);
			}	
			printf("Inserire elemento\n");
			scanf("%d", &elem);
			testa->info = elem;
			testa->next = NULL;
			testa->prev = NULL;
			curr = testa;
		}
		else{
			curr = (struct elem*)malloc(sizeof(struct elem));
			if (curr == NULL) {
	   			printf("Errore: impossibile allocare memoria.\n");
	    		exit(1);
			}	
			printf("Inserire elemento\n");
			scanf("%d", &elem);
			curr->info = elem;
			curr->next = NULL;
			curr->prev = prec;
			
			if(n_elem == 1){
				curr->next = testa;
				testa->prev = curr;
			}
			
		}
				
		if (n_elem == 0) {
		    return NULL;
		}
		else {
		    n_elem--;
		}
		
		curr->next = crea_lista(n_elem, curr, curr->next, testa);
	}
	
	return testa;
}



void print_lista(struct elem* testa, int n){
	
	if(n != 0){
		if (testa != NULL) {
    		printf("|%d| ", testa->info);
		}
		n = n - 1;
		print_lista(testa->next, n);
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


