
#include <stdio.h>
#include <malloc.h>

struct el
{
	struct el *prev;
	int inf;
	struct el *next;
};

struct el *crea_lista(int n, struct el* testa, struct el* testa1);
struct el *inserisci(struct el*,int);
void visualizza_lista(struct el *lista);
struct el* inserisci_testa(struct el* L, int valore);

int main(){
	struct el *lista;
	int valore,valore2;
	int liste = 1;
	struct el* testa = NULL;
	int n = 0;
	
	while(liste != 0){
		printf("Specificare numero di elementi\n");
		scanf("%d", &n);
		lista=crea_lista(n, testa, testa); 
		/*printf("\nInserisci elemento da inserire in coda: ");
		scanf("%d", &valore);
		lista=inserisci(lista,valore);
		visualizza_lista(lista);
		printf("\nInserisci elemento da inserire in testa: ");
		scanf("%d", &valore2);
		inserisci_testa(lista, valore2);
		visualizza_lista(lista);*/
		liste--;
	}
}


//lista doppiamente puntata
struct el *crea_lista(int n, struct el* testa, struct el* testa1) {
	
	if(n != 0){
		
		testa=(struct el *)malloc(sizeof(struct el));
		printf("inserire primo elemento\n");
		scanf("%d",&testa->inf);
		testa->next = NULL; //da inserire per dare un next iniziale
		testa->prev = testa1;
		testa1 = testa;
		
		n = n - 1;
		testa->next = crea_lista(n, testa->next, testa1);
	}
	
	return(testa);
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
			ultimo_nodo = testa; //utilizziamo un puntatore per puntare all'ultimo elemento che poi servirà durante la risalita
		}
		
		n = n - 1;
		testa->next = crea_lista(n, testa->next, testa1, testa_lista, ultimo_nodo);
		
		if(testa->prev == NULL){//se il nodo attuale è quello in testa (unico con testa->prev = NULL)
			testa->prev = ultimo_nodo; //imposta come precedente del nodo in testa, l'ultimo nodo della lista (memorizzato durante la discesa delle chiamate ricorsive)
		}
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


