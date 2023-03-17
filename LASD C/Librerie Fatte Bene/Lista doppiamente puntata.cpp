
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

int main(){
	struct el *lista;
	int valore,valore2;
	int liste = 1;
	struct el* testa = NULL;
	int n = 0;
	
	while(liste != 0){
		printf("Specificare numero di elementi\n");
		scanf("%d", &n);
		lista=crea_lista(n); 
		/*printf("\nInserisci elemento da inserire in coda: ");
		scanf("%d", &valore);
		lista=inserisci(lista,valore);
		visualizza_lista(lista);
		printf("\nInserisci elemento da inserire in testa: ");
		scanf("%d", &valore2);
		inserisci_testa(lista, valore2);
		visualizza_lista(lista);*/
		print_lista_dopp(lista, n);
		liste--;
	}
}


/*Lista doppiamente puntata circolare*/
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
        punt->next = p; // lista circolare: l'ultimo elemento punta alla testa
        p->prev = punt; // la testa punta all'ultimo elemento
    } // chiudo l'if-else
    return(p); // ritorno il puntatore alla testa
} // chiudo la funzione



//lista doppiamente puntata circolare
struct el *crea_lista(int n, struct el* testa, struct el* testa1, struct el* testa_lista, struct el* ultimo_nodo) {
	
	if(n != 0){
		
		testa=(struct el *)malloc(sizeof(struct el));
		printf("inserire primo elemento\n");
		scanf("%d",&testa->inf);
		testa->next = NULL; //da inserire per dare un next iniziale
		testa->prev = testa1;
		testa1 = testa;
		
		//se è l'ultimo elemento
		if(n == 1){
			testa->next = testa_lista; //imposta come successivo dell'ultimo nodo il primo nodo della lista
			testa_lista->prev = testa; //imposta come precedente dell'elemento in testa l'elemento in coda
		}
		
		n = n - 1;
		testa->next = crea_lista(n, testa->next, testa1, testa_lista, ultimo_nodo);

	}
	
	
	return(testa);
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


void print_lista_dopp(struct el *p, int n) {
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

//inserimento in testa
struct el* inserisci_testa(struct el* L, int valore){
	struct el*punt;
	if(L==NULL){
		L=(struct el*)malloc(sizeof(struct el*));
		L->inf=valore;
		L->prev=NULL;
		L->next=NULL;
		
	}
	else{
		punt=L;
		punt=(struct el*)malloc(sizeof(struct el*));
		punt->prev=NULL;
		punt->inf=valore;
		punt->next=L;
		punt->next->prev=punt;
		L=punt;
		
	}
	return L;
}


