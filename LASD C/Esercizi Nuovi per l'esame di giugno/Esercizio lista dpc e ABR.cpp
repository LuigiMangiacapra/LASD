/*Creare una lista doppiamente puntata circolare e un albero, inserire tutti gli elementi dispari della lista nell'albero ed eliminarli dalla lista*/

#include <stdio.h>
#include <stdlib.h>

//Strutura lista
struct circular_elem{
	struct circular_elem *prev;
	int inf;
	struct circular_elem *next;
};

//Struttura albero
struct albero_elem{
	int inf;
	struct albero_elem *sinistro, *destro;	
};


struct albero_elem* crea_nodo(struct albero_elem* sinistro, struct albero_elem* destro, int elem){
	struct albero_elem* padre;
	padre=(struct albero_elem*)malloc(sizeof(struct albero_elem));
	if(padre != NULL){
		padre->inf=elem;
		padre->destro=destro;
		padre->sinistro=sinistro;
	}
	return padre;
}

struct circular_elem *crea_lista(int n);
void print_lista_dopp(struct circular_elem *p);
struct albero_elem* inserisci(struct albero_elem* radice, int k);
void stampa_in_ordine(struct albero_elem* radice);
struct albero_elem* delete_odd_elem_and_add_to_tree(struct circular_elem** nodo, struct albero_elem* radice, int num_elem);

int main(){
	struct circular_elem *lista = NULL;
	int valore, valore2;
	int liste = 1;
	struct circular_elem* testa = NULL;
	int num_elem_lista = 0, num_elem_albero = 0;
	struct albero_elem* radice = NULL;
	int elem = 0;
	int i = 0;
	
	
	//LISTA
	printf("Specificare numero di elemementi della lista\n");
	scanf("%d", &num_elem_lista);
	lista=crea_lista(num_elem_lista); 
	
	printf("Lista doppiamente puntata circolare inserite:\n");
	print_lista_dopp(lista);
	
	
	
	//ALBERO
	printf("Specificare numero di elementi dell'albero\n");
	scanf("%d", &num_elem_albero);
	
	while(num_elem_albero != 0){
		i++;
		printf("Inserire elemento %d: ", i);
		scanf("%d", &elem);
		
		radice = inserisci(radice, elem);
		num_elem_albero--;
	}
	
	printf("Albero binario di ricerca inserito:\n");
	stampa_in_ordine(radice);
	
	printf("\n");
	
	//LISTA E ALBERO DOPO LE MODIFICHE
	delete_odd_elem_and_add_to_tree(&lista, radice, num_elem_lista);
	
	printf("Lista doppiamente puntata dopo le modifiche:\n");
	print_lista_dopp(lista);
	
	printf("Albero ABR dopo le modifiche:\n");
	stampa_in_ordine(radice);
}


/*Lista doppiamente puntata circolare*/
struct circular_elem *crea_lista(int n) {
    struct circular_elem *p, *punt;
    int i;
    if(n==0) {
        p = NULL;
    } else {
        /* creazione primo circular_elememento */
        p = (struct circular_elem*)malloc(sizeof(struct circular_elem));
        printf("\nInserisci il primo valore: ");
        scanf("%d", &p->inf);
        punt = p;
        p->prev = NULL;
        for(i=2; i<=n; i++) {
            punt->next = (struct circular_elem *)malloc(sizeof(struct circular_elem));
            punt->next->prev = punt;
            punt = punt->next;
            printf("\nInserisci il %d elememento: ", i);
            scanf("%d", &punt->inf);
        } // chiudo il for
        punt->next = p; // lista circolare: l'ultimo circular_elememento punta alla testa
        p->prev = punt; // la testa punta all'ultimo circular_elememento
    } // chiudo l'if-circular_elemse
    return(p); // ritorno il puntatore alla testa
} // chiudo la funzione



void print_lista_dopp(struct circular_elem *p) {
	if (p == NULL) {
        printf("La lista è vuota\n");
        return;
    }
    
    struct circular_elem* start = p;
    
    do {
        printf("%d", p->inf); /* visualizza l'informazione */
        printf(" ---> ");
        p = p->next;
    } while (p != start);
    
    printf("...\n\n");
} 



//inserisce nodo nell'albero 
struct albero_elem* inserisci(struct albero_elem* radice, int k){
	
	if(radice==NULL)
		radice = crea_nodo(NULL, NULL,k);//Ricordare sempre il tipo di ritorno di una funzione che modifica la struttura
	else{
		if(radice->inf<k)
			radice->destro=inserisci(radice->destro,k);
		else if(radice->inf>k)
			radice->sinistro=inserisci(radice->sinistro,k);
	}
	return radice;
}


//stampa l'albero in ordine
void stampa_in_ordine(struct albero_elem* radice){
	if(radice!=NULL){
		stampa_in_ordine(radice->sinistro);
		printf(" |%d| ",radice->inf);
		stampa_in_ordine(radice->destro);
		
	}
			
}


struct albero_elem* delete_odd_elem_and_add_to_tree(struct circular_elem** nodo, struct albero_elem* radice, int num_elem){
	struct circular_elem* tmp;
    if (num_elem != 0) {
        if ((*nodo)->inf % 2 != 0) {
            radice = inserisci(radice, (*nodo)->inf);
            tmp = *nodo;
            
            //Quando dobbiamo eliminare il nodo 'nodo' dobbiamo modificare tutti i puntatori verso di lui
            //1) Modifica il puntatore successivo del precedente di 'nodo' con il successivo di 'nodo'
            (*nodo)->prev->next = (*nodo)->next;
            
			//2) Modifica il precedente del successivo di 'nodo' con il precedente di 'nodo'
            (*nodo)->next->prev = (*nodo)->prev;
            *nodo = (*nodo)->next;
            free(tmp);
        } 
		else {
            *nodo = (*nodo)->next;
        }
        
        num_elem--;
        radice = delete_odd_elem_and_add_to_tree(nodo, radice, num_elem);
    }
    
    return radice;
}
