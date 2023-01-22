/*
Creare una lista e sostituire ogni elemento in posizione dispari con il doppio 
dell'elemento che lo precede
	esempio:
		input: 1 2 3 4 5
		output: 1 2 4 4 8
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20

struct elem *crea_lista();
void visualizza_lista(struct elem *lista);
struct elem* sostituisci_dispari(struct elem *lista, struct elem *elem, int pos);

struct elem{
	int inf;
	struct elem *next;
};

int main(){
	int pos=0;
	struct elem* elem = NULL;
	struct elem *lista = NULL; //puntatore che si collega alla struct per creare la lista
	lista=crea_lista();
	lista = sostituisci_dispari(lista, elem, pos);
	visualizza_lista(lista);
}


struct elem *crea_lista(){
	struct elem *testa, *punt;
	int i, n;
	printf("Specificare numero di elementi\n");
	scanf("%d", &n);
	
	if(n==0){
		testa=NULL;
	}
	else{
		testa=(struct elem *)malloc(sizeof(struct elem));
		printf("inserire primo elemento\n");
		scanf("%d",&testa->inf);
		punt=testa;
		for(i=2;i<=n;i++){
			punt->next=(struct elem *)malloc(sizeof(struct elem));
			punt=punt->next;
			printf("inserire il %d elemento:\n",i);
			scanf("%d",&punt->inf);
		
		}
		punt->next=NULL;
	
	}
	return(testa);
}


void visualizza_lista(struct elem *p) {
	printf("\n lista ---> ");
	while(p != NULL){
		printf("%d", p->inf); /* visualizza l'informazione */
		printf(" ---> ");
		p = p->next; /* scorre la lista di un elemento */
	}
	printf("NULL\n\n"); 
} 


struct elem* sostituisci_dispari(struct elem *lista, struct elem *elem, int pos){
	
	if(lista != NULL){
		
		pos = pos + 1;
		if(pos % 2 == 0){
			elem = lista;
			printf("elem:%d\n", elem->inf);
		}
		printf("pos_scesa:%d\n", pos);
		lista->next = sostituisci_dispari(lista->next, elem, pos);
		printf("pos_salita:%d\n", pos);
		
		//pos deve essere != da 1 perché non ci sono posizioni precedenti ad 1, elem di conseguenza
		//non ha valore
		if(pos % 2 != 0 && pos != 1){
			lista->inf = 2 * elem->inf;
			printf("inf:%d\n", lista->inf);
		}
	}
	printf("Uscito\n");
	return lista;
}


