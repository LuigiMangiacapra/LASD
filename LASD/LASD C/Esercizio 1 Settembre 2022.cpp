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
void visualizza_lista(struct el *lista);
struct el *rimpiazza_dispari(struct el* lista, struct el* disp, int somma, int n_elem, int count, int pos);

int main(){
	struct el *lista = NULL;
	struct el* disp = NULL;
	struct el* testa = NULL;
	int count = 0, media = 0, somma = 0, n, pos = 0;
	printf("\n Specificare il numero di elementi... ");
	scanf("%d", &n);
	lista=crea_lista(n); 
	visualizza_lista(lista);
	testa = lista;
	while(lista != NULL){
		
		somma = somma + lista->inf;
		lista = lista->next;
	}
	
	count = n;
	lista=rimpiazza_dispari(testa, disp, somma, n, count, pos);
	visualizza_lista(testa);
	
}


struct el *crea_lista(int n) {
	struct el *p, *punt;
	int i;
	if(n==0) 
		p = NULL; 
	else {
		/* creazione primo elemento */
		p = (struct el *)malloc(sizeof(struct el));
		printf("\nInserisci il primo valore: ");
		scanf("%d", &p->inf);
		punt = p; p-> prev=NULL;
		for(i=2; i<=n; i++)
		{	
			punt->next = (struct el *)malloc(sizeof(struct el));
			punt->next->prev=punt;
			punt = punt->next;
			printf("\nInserisci il %d elemento: ", i);
			scanf("%d", &punt->inf);
		} // chiudo il for
		punt->next = NULL; // marcatore fine lista
	} // chiudo l'if-else
	return(p);
} // chiudo la funzione


void visualizza_lista(struct el *p) {
	printf("\nlista ---> ");
	while(p != NULL){
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 


//rimpiazzare ogni elemento dispari con la media degli altri elementi
struct el *rimpiazza_dispari(struct el* lista, struct el* disp, int somma,  int n_elem, int count, int pos){
	
	
	if(n_elem > 0){
		
		n_elem = n_elem - 1;
		pos = pos + 1;
		
		if(pos % 2 != 0){
			disp = lista;
		}
		
		rimpiazza_dispari(lista->next, disp, somma, n_elem, count, pos);
		
		if(lista == disp){
			disp->inf = (somma - lista->inf)/(count - 1);
		}
		
	}
	
	return lista;
}



