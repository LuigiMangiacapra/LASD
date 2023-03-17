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
int somma_elem(struct elem* testa, int somma, int n);
struct elem* substitute_even(int n_elem, struct elem* testa, int somma);
struct elem* funzione_esercizio(int n_elem, struct elem* testa, int n);


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
	
	lista = crea_lista(n_elem);
	
	print_lista(lista, n_elem);
	
	printf("\n");
	
	lista = funzione_esercizio(n_elem, lista, n_elem);
	
	print_lista(lista, n_elem);
}


/*Lista doppiamente puntata circolare*/
struct elem *crea_lista(int n) {
    struct elem *p, *punt;
    int i;
    if(n==0) {
        p = NULL;
    } else {
        /* creazione primo elemento */
        p = (struct elem*)malloc(sizeof(struct elem));
        printf("\nInserisci il primo valore: ");
        scanf("%d", &p->info);
        punt = p;
        p->prev = NULL;
        for(i=2; i<=n; i++) {
            punt->next = (struct elem *)malloc(sizeof(struct elem));
            punt->next->prev = punt;
            punt = punt->next;
            printf("\nInserisci il %d elemento: ", i);
            scanf("%d", &punt->info);
        } // chiudo il for
        punt->next = p; // lista circolare: l'ultimo elemento punta alla testa
        p->prev = punt; // la testa punta all'ultimo elemento
    } // chiudo l'if-else
    return(p); // ritorno il puntatore alla testa
} // chiudo la funzione



void print_lista(struct elem *p, int n) {
	printf("\nlista ---> ");
	int i = 0 ;
	while(i < n){
		
		printf("%d", p->info); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next;
		i++; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 


int somma_elem(struct elem* testa, int somma, int n){
	
	if(n != 0){
		somma = somma + testa->info;
		n = n - 1;
		somma = somma_elem(testa->next, somma, n);
	}
	return somma;
}


struct elem* substitute_even(int n_elem, struct elem* testa, int somma){
	
	if(n_elem != 0){
		
		n_elem = n_elem - 1;
		substitute_even(n_elem, testa->next, somma);
		
		if(testa->info % 2 == 0){
			testa->info = somma - testa->info;
		}
	}
	
	return testa;
}


struct elem* funzione_esercizio(int n_elem, struct elem* testa, int n){
	int somma;
	somma = somma_elem(testa, somma, n);
	
	substitute_even(n_elem, testa, somma);
}
