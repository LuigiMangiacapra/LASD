

/*Eliminare tutti gli elementi pari dalla prima lista e insserire il numero di elementi rimanenti in coda alla seconda lista*/

#include <stdio.h>
#include <malloc.h>

struct el
{
	struct el *prev;
	int inf;
	struct el *next;
};

struct el *crea_lista(int n);
struct el* inserisci_coda(struct el* lista, int elem);
void visualizza_lista(struct el *lista);
struct el* inserisci_testa(struct el* L, int valore);
void esercizio(struct el** l1, struct el** l2, int elem_rim);

int main(){
	struct el *lista = NULL, *lista2 = NULL;
	int valore,valore2;
	int liste = 1;
	struct el* testa = NULL;
	int n = 0, n2 = 0;
	int elem = 0;
	int pos = 0;
	int somma = 0;
	int media = 0;
	int i, j;
	int elem1, elem2;
	int elem_rim = 0;
	
	printf("Creazione prima lista\n");
	printf("Specificare numero di elementi\n");
	scanf("%d", &n);
	//lista=crea_lista(n);
	for(i=0; i<n; i++){
		printf("Inserire elemento\n");
		scanf("%d", &elem1);
		lista=inserisci_coda(lista, elem1);
	}
	visualizza_lista(lista);
	
	printf("\nCreazione seconda lista\n");
	printf("Specificare numero di elementi\n");
	scanf("%d", &n2);
	//lista2=crea_lista(n2);
	for(j=0; j<n2; j++){
		printf("Inserire elemento\n");
		scanf("%d", &elem2);
		lista2=inserisci_coda(lista2, elem2);
	}
	visualizza_lista(lista2);
	
	
	esercizio(&lista, &lista2, elem_rim);
	
	printf("Stampa liste dopo modifiche\n");
	visualizza_lista(lista);
	visualizza_lista(lista2);
}



struct el* inserisci_coda(struct el* lista, int elem) {
    struct el* new_nodo;

    if (lista == NULL) {
        new_nodo = (struct el*)malloc(sizeof(struct el));
        new_nodo->inf = elem;
        new_nodo->next = NULL;
        return new_nodo;
    }

    if (lista->next != NULL) {
        lista->next = inserisci_coda(lista->next, elem);
    }
    else {
        new_nodo = (struct el*)malloc(sizeof(struct el));
        new_nodo->inf = elem;
        new_nodo->next = NULL;
        lista->next = new_nodo;
    }

    return lista;
}

/*//Lista doppiamente puntata
struct el *crea_lista(int n) {
    struct el *p, *punt;
    int i;
    if(n==0) {
        p = NULL;
    } else {
        // creazione primo elemento 
        p = (struct el*)malloc(sizeof(struct el));
        printf("\nInserisci il primo valore: ");
        scanf("%d", &p->inf);
        punt = p;
        p->prev = NULL;
        for(i=2; i<=n; i++) {
            punt->next = (struct el *)malloc(sizeof(struct el));
            punt->next->prev = punt;
            punt = punt->next;
            printf("\nInserisci il %d elemento: ", i);
            scanf("%d", &punt->inf);
        } // chiudo il for
        punt->next = NULL;
    } // chiudo l'if-else
    return(p); // ritorno il puntatore alla testa
} // chiudo la funzione

*/


void visualizza_lista(struct el *p) {
	printf("\nlista ---> ");
	while(p != NULL){
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 


//inserimento in testa
struct el* inserisci_testa(struct el* L, int valore){
	struct el*punt, *new_elem;
	
	new_elem=(struct el*)malloc(sizeof(struct el*));
	new_elem->inf=valore;
	new_elem->prev=NULL;
	new_elem->next=L;
	L = new_elem;

	return L;
}

void esercizio(struct el** l1, struct el** l2, int elem_rim){
	struct el* tmp;
	struct el* new_elem;
	
	if((*l1) != NULL){
		
		if((*l1)->inf % 2 == 0){
			tmp = (*l1);
			
			if((*l1)->next != NULL){
				(*l1)->next->prev = (*l1)->prev;
			}
			
			(*l1) = (*l1)->next;
			free(tmp);	
			esercizio(l1, l2, elem_rim);
		}
		else{
			elem_rim++;
			l1 = &((*l1)->next);
			esercizio(l1, l2, elem_rim);
		}
			
	}
	else if((*l2) != NULL){
	
		esercizio(l1, &(*l2)->next, elem_rim);
		
		if((*l2)->next == NULL){
			new_elem = (struct el*)malloc(sizeof(struct el));
			new_elem->inf = elem_rim;
			new_elem->next = NULL;
			(*l2)->next = new_elem;
		}
		
	}
	
	
}
