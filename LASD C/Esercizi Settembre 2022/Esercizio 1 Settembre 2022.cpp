/*
Data una lista doppiamente puntata e circolare, scrivere una funzione che rimpiazzi ogni elemento
in posizione dispari con la media tra gli elementi alla sua destra e alla sua sinistra.
Per la numerazione delle posizioni, si assuma che il primo elemento si trovi in posizione 1,

*/
#include <stdio.h>
#include <malloc.h>

struct el
{
	struct el *prev;
	int inf;
	struct el *next;
};

struct el *crea_lista(int n);  
void visualizza_lista(struct el *lista, int n);
void replaceOddWithAverage(struct el* current, struct el* head, int sum, int count);
void replaceOddValues(struct el* head, struct el* current);
int sum(struct el* head);
int replaceOddElements(struct el* head, struct el* curr, int sum);

int main(){
	struct el *lista = NULL;
	struct el* disp = NULL;
	struct el* testa = NULL;
	int count = 0, media = 0, somma = 0, somma2 = 0, n, pos = 0, i=0;
	
	printf("\n Specificare il numero di elementi... ");
	scanf("%d", &n);
	lista=crea_lista(n); 
	visualizza_lista(lista, n);
	
	testa = lista;
	
	/*while(i < n){
		
		somma = somma + lista->inf;
		i++;
		lista = lista->next;
	}*/

	//replaceOddValues(lista, lista);
	struct el* curr = lista;

	replaceOddElements(lista, curr, somma);
	
	visualizza_lista(lista, n);
	
}


/*Lista doppiamente puntata circolare*/
struct el *crea_lista(int n) {
    struct el *p, *punt;
    int i;
    if(n==0) {
        p = NULL;
    } else {
        /* creazione primo elemento */
        p = (struct el *)malloc(sizeof(struct el));
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
        punt->next = p; // lista circolare: l'ultimo elemento punta alla testa
        p->prev = punt; // la testa punta all'ultimo elemento
    } // chiudo l'if-else
    return(p); // ritorno il puntatore alla testa
} // chiudo la funzione


void visualizza_lista(struct el *p, int n) {
	printf("\nlista ---> ");
	int i = 0 ;
	while(i < n){
		
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next;
		i++; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 


// Funzione per calcolare la somma degli elementi nella lista
int sum(struct el* head) {
    int total = 0;
    struct el* current = head;

    do {
        total += current->inf;
        current = current->next;
    } while (current != head);

    return total;
}

// Funzione ricorsiva per sostituire i valori dispari con la somma degli altri elementi
/*void replaceOddValues(struct el* head, struct el* current) {


	if (current->inf % 2 != 0) {
	    int total = sum(head) - current->inf;
	    current->inf = total;
		current = current->next;        
	}

	if(current != head){
		
	    if (current->inf % 2 != 0) {
	        int total = sum(head) - current->inf;
	        current->inf = total;
	        
	    }
	    replaceOddValues(head, current->next);
	}
}
*/



int replaceOddElements(struct el* head, struct el* curr, int sum) {
    if (head == NULL)
        return sum;

	if (curr->next == head){
		sum += curr->inf;
		return sum;
	}
    
    sum += curr->inf;

    sum = replaceOddElements(head, curr->next, sum);
    
    if (curr->inf % 2 != 0){
    	curr->inf = sum - curr->inf;
    	sum = replaceOddElements(head, curr->next, sum);
	}
        
        
    
}


