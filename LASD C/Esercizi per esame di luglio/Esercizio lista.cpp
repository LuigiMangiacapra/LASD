
/*Eliminare nella prima lista tutti gli elementi in posizione dispari e inserire la media in coda alla seconda lista*/


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
void esercizio(struct el** l1, struct el** l2, int pos, int somma, int media, int n_elem);

int main(){
	struct el *lista, *lista2;
	int valore,valore2;
	int liste = 1;
	struct el* testa = NULL;
	int n = 0, n2 = 0;
	int elem = 0;
	int pos = 0;
	int somma = 0;
	int media = 0;
	
	printf("Creazione prima lista\n");
	printf("Specificare numero di elementi\n");
	scanf("%d", &n);
	lista=crea_lista(n); 
	visualizza_lista(lista);
	
	printf("\nCreazione seconda lista\n");
	printf("Specificare numero di elementi\n");
	scanf("%d", &n2);
	lista2=crea_lista(n2);
	visualizza_lista(lista2);
	
	
	esercizio(&lista, &lista2, pos, somma, media, 1);
	
	printf("Stampa liste dopo modifiche\n");
	visualizza_lista(lista);
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


void esercizio(struct el** l1, struct el** l2, int pos, int somma, int media, int n_elem){

	struct el* tmp;
	
	if((*l1) != NULL){
		pos++;
		
		if(pos % 2 != 0){
			n_elem++;
			somma+= (*l1)->inf;
			tmp = (*l1);
			
			if(tmp->next != NULL){
				tmp->next->prev = tmp->prev;
			}
            
            if((*l1)->next == NULL){
				media = (somma + (*l1)->inf)/n_elem;
			}
			
			(*l1) = (*l1)->next;
            free(tmp);
            
			esercizio(l1, l2, pos, somma, media, n_elem);
		}
		else{
			l1 = &((*l1)->next);
			esercizio(l1, l2, pos, somma, media, n_elem);
		}
				
		
	}	
	else if((*l2) != NULL){
		struct el* new_elem = (struct el*)malloc(sizeof(struct el));
		new_elem->inf = media;
		new_elem->next = NULL;
		
		esercizio(l1, &(*l2)->next, pos, somma, media, n_elem);
		
		if((*l2)->next == NULL)
			(*l2)->next = new_elem;
	}
	
}


