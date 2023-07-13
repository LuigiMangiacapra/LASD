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
void print_lista_dopp(struct circular_elem *p);
struct circular_elem* elimina(struct circular_elem* lista, int elem);
struct circular_elem* elimina_dup(struct circular_elem* lista, struct circular_elem* testa, int elem);

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
	print_lista_dopp(lista);
	
	printf("Inserire l'elemento da eliminare\n");
	scanf("%D", &elem);
	//lista = elimina(lista, elem);
	
	testa = lista;
	lista = elimina_dup(lista, testa, elem);
	
	printf("\nstampa dopo l'eliminazione\n");
	print_lista_dopp(lista);

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
	struct circular_elem* curr = p;
	printf("\nlista ---> ");
	int i = 0 ;
	if(p == NULL){
		printf("La lista è vuota\n");
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


struct circular_elem* elimina(struct circular_elem* lista, int elem) {
    struct circular_elem* tmp;

    if (lista == NULL) {
        return lista;
    }
    else{
        if (lista->inf == elem) { 
        	tmp = lista;
            lista = lista->next;
            free(tmp);
            
            //lista = elimina(lista, elem); //Se si vogliono eliminare duplicati
        } 
		else {
            lista->next = elimina(lista->next, elem);
        }
    }

    
    return lista;
}


//Elimina duplicati
struct circular_elem* elimina_dup(struct circular_elem* lista, struct circular_elem* testa, int elem) {
    
    struct circular_elem* tmp;
    
    if(lista->next == testa){
    	
    	if (lista->inf == elem) {
	    	tmp = lista;
	        lista = lista->next;
	        free(tmp);
	    }
	    return lista;
	}

    if (lista->inf == elem) {
        tmp = lista;
        lista = lista->next;
        free(tmp);
        
        lista = elimina_dup(lista, testa, elem);
    }
	else{
		
		lista->next = elimina_dup(lista->next, testa, elem);
	}
    	
}


