
/*Data una lista doppiamente puntata e cricolare, scrivere una funzione che rimpiazzi ogni elemento pari con la somma degli elemento alla sua destra e alla sua sinistra*/

#include <stdio.h>
#include <malloc.h>

struct el
{
	struct el *prev;
	int inf;
	struct el *next;
};

struct el *crea_lista(int n);
struct el* inserisci(int n);
void visualizza_lista(struct el *lista);
struct el* inserisci_testa(struct el* L, int valore);
struct el* esercizio(struct el* lista, int n, struct el* prev, struct el* next);
int main(){
	struct el *lista = NULL, *lista2 = NULL;
	int valore,valore2;
	int liste = 1;
	struct el* testa = NULL, *testa2 = NULL;
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
	testa = inserisci(n);
	
	visualizza_lista(testa);
	
	/*printf("\nCreazione seconda lista\n");
	printf("Specificare numero di elementi\n");
	scanf("%d", &n2);
	
	testa2 = inserisci(n2);

	visualizza_lista(testa2);
	*/
	struct el* prev = lista->prev;
	struct el* next = lista->next;
	lista = esercizio(lista, n, prev, next);
	
	printf("Stampa liste dopo modifiche\n");
	visualizza_lista(testa);
	//visualizza_lista(testa2);
}



struct el* inserisci(int n) {
    struct el *p, *punt;
    int i;
    if(n==0) {
        p = NULL;
    } else {
        /* creazione primo circular_elememento */
        p = (struct el*)malloc(sizeof(struct el));
        printf("\nInserisci il primo valore: ");
        scanf("%d", &p->inf);
        punt = p;
        p->prev = NULL;
        for(i=2; i<=n; i++) {
            punt->next = (struct el *)malloc(sizeof(struct el));
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


void visualizza_lista(struct el* p) {
    struct el* curr = p;
	printf("\nlista ---> ");
	
	if(p == NULL){
		printf("La lista e' vuota\n");
		return;
	}
	do{
		printf("%d", curr->inf);
		printf(" ---> ");
		curr = curr->next;
	}
	while(curr != p);
	
	printf("...\n\n"); 
}


struct el* esercizio(struct el* lista, int n){
	
	struct el* tmp;
	if(n != 0){
		
		if(lista->inf % 2 == 0){			
			
			if(lista->prev != NULL && lista->next != NULL)
				lista->inf = (lista->prev->inf + lista->next->inf);
		}
		
		lista->next = esercizio(lista->next, n - 1);
	}
	return lista;
}



