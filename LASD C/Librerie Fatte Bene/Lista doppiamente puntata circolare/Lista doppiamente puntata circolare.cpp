/*Lista doppiamente puntata circolare*/


#include <stdio.h>
#include <stdlib.h>

struct circular_elem
{
	struct circular_elem *prev;
	int inf;
	struct circular_elem *next;
};

struct circular_elem *crea_lista(int n);
void print_lista_dopp(struct circular_elem *p, int n);
struct circular_elem* elimina(struct circular_elem* lista, int elem);

int main(){
	struct circular_elem *lista;
	int valore,valore2;
	int liste = 1;
	struct circular_elem* testa = NULL;
	int n = 0;
	int elem = 0;
	
	printf("Specificare numero di elemementi\n");
	scanf("%d", &n);
	lista=crea_lista(n); 
	print_lista_dopp(lista, n);
	
	printf("Inserire l'elemento da eliminare\n");
	scanf("%D", &elem);
	lista = elimina(lista, elem);
	
	printf("\nstampa dopo l'eliminazione\n");
	print_lista_dopp(lista, n);

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


void print_lista_dopp(struct circular_elem *p, int n) {
	printf("\nlista ---> ");
	int i = 0 ;
	if(p == NULL){
		printf("La lista � vuota\n");
		return;
	}
	while(i < n){
		
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next;
		i++; /* scorre la lista di un circular_elememento */
	}
	printf("...\n\n"); 
} 


struct circular_elem* elimina(struct circular_elem* lista, int elem) {
    struct circular_elem* tmp;
	printf("|%d| ", lista->inf);
	//Se le due liste sono vuote o se si � arrivati con entrambe le liste a NULL
    if (lista == NULL) {
    	printf("NULL");
        return lista;
    }
    else{
        if (lista->inf == elem) { 
        	tmp = lista;
        	
        	lista->prev->next = lista->next;
			lista->next->prev = lista->prev;

            lista = lista->next;
            free(tmp);
            
            //lista = deleteNode(lista, elem); //Se si vogliono eliminare duplicati
        } 
		else {
            lista->next = elimina(lista->next, elem);
        }
    }

    
    return lista;
}


