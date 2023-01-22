
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
struct el *rimpiazza_dispari(struct el *testa, struct el *lista, int somma, int count);

int main(){
	struct el *lista;
	struct el* testa;
	int valore,valore2;
	int n, somma, count, somma2;
	printf("\n Specificare il numero di elementi... ");
	scanf("%d", &n);
	testa=crea_lista(n); 
	lista = testa->next;
	visualizza_lista(testa);
	
	lista=rimpiazza_dispari(testa, lista, somma, count);
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
struct el *rimpiazza_dispari(struct el* testa, struct el* lista, int somma, int count){
	
	if(lista != testa){ 
	
		somma = somma + lista->inf;
		count = count + 1;
		
		//Funzione ricorsiva che scorre tutti gli elementi
		lista->next = rimpiazza_dispari(testa, lista->next, somma, count);
		
		somma = somma + lista->inf;
		count = count + 1;
		
		lista->next = rimpiazza_dispari(testa, lista->prev, somma, count);
		
		if(lista->inf %2 != 0)
			lista->inf = (somma - lista->inf)/(count - 1);
	}
	return lista;
}



