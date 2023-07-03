/*Creare una funzione in cui si eliminano tutte le occorrenze di 2 nella prima lista e si inserisce in testa il numero delle occorrenze di 2*/


#include <stdio.h>
#include <malloc.h>

struct el
{
	struct el *prev;
	int inf;
	struct el *next;
};

struct el *crea_lista(int n);
struct el *inserisci(struct el*,int);
void visualizza_lista(struct el *lista);
struct el* inserisci_testa(struct el* L, int valore);
void print_lista_dopp(struct el *p, int n);
void funzione_esercizio(struct el** l1, struct el** l2, int numero_elementi);

int main(){
	struct el *lista, *lista2;
	int valore,valore2;
	int liste = 1;
	struct el* testa = NULL;
	int n = 0, n2 = 0;
	int elem = 0;
	int numero_elementi = 0;
	
	printf("Specificare numero di elementi prima lista\n");
	scanf("%d", &n);
	lista=crea_lista(n); 
	visualizza_lista(lista);
	
	printf("Specificare numero di elementi seconda lista\n");
	scanf("%d", &n2);
	lista2=crea_lista(n2); 
	visualizza_lista(lista2);
	
	
	funzione_esercizio(&lista, &lista2, numero_elementi);
	
	
	printf("\nStampa lista1\n");
	visualizza_lista(lista);
	
	printf("\nStampa lista2\n");
	visualizza_lista(lista2);
	
}


/*Lista doppiamente puntata*/
struct el *crea_lista(int n) {
    struct el *p, *punt;
    int i;
    if(n==0) {
        p = NULL;
    } else {
        /* creazione primo elemento */
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


struct el *inserisci(struct el *p, int valore)
{ 
	struct el *nuovo=NULL;
	struct el *testa;
	if (p==NULL) {
		p=(struct el *)malloc(sizeof(struct el));
		p->inf=valore;
		p->prev=NULL; 
		testa=p; 
	}
	else {
		testa=p;
		if (p->next!= NULL) 
			inserisci(p->next, valore);
		nuovo=(struct el *)malloc(sizeof(struct el));
		nuovo->prev=p;
		nuovo->inf=valore;
		nuovo->next = NULL; 
	}
	p->next=nuovo; 
	return testa;
}

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


void funzione_esercizio(struct el** l1, struct el** l2, int numero_elementi){
	struct el* tmp, *new_elem;
	
	
	if((*l1) != NULL || (*l2) != NULL){
		
		if((*l1) != NULL){
			printf("%d\n", (*l1)->inf);
			if((*l1)->inf == 2){
				
				numero_elementi+=1;
				tmp = (*l1);
				(*l1) = (*l1)->next;
				free(tmp);
				funzione_esercizio(l1, l2, numero_elementi);
			}
			else{
				l1 = &((*l1)->next);
				funzione_esercizio(l1, l2, numero_elementi);
			}
				
		}
		else if((*l2) != NULL){
			new_elem = (struct el*)malloc(sizeof(struct el));
			new_elem->inf = numero_elementi;
			new_elem->next = (*l2);
			(*l2) = new_elem;
		}
			
	}
}
