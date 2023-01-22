
#include <stdio.h>
#include <malloc.h>

struct el
{
	struct el *prev;
	int inf;
	struct el *next;
};

struct el *crea_lista();
void visualizza_lista(struct el *lista);
struct el* conc_liste(struct el* l1, struct el* l2);

int main(){
	struct el *lista1, *lista2;
	int valore;
	int liste;
	printf("Quante liste vuoi creare?\n");
	scanf("%d",&liste);
	
	while(liste){
		if(liste==2){
			lista1=crea_lista();
			visualizza_lista(lista1);
		}
		if(liste==1){
			lista2=crea_lista();
			visualizza_lista(lista2);
		}
		
		liste--;
	}
	
	printf("\n");
	lista2=conc_liste(lista1, lista2);
	visualizza_lista(lista2);
	printf("Lista 2 modificata\n");
}


struct el *crea_lista() {
	struct el *p, *punt;
	int i, n;
	printf("\nSpecificare il numero di elementi\n");
	scanf("%d",&n);
	if(n==0) 
		p = NULL; 
	else {
		/* creazione primo elemento */
		p = (struct el *)malloc(sizeof(struct el));
		printf("\nInserisci il primo valore:\n");
		scanf("%d", &p->inf);
		punt = p; p-> prev=NULL;
		for(i=2; i<=n; i++)
		{	
			punt->next = (struct el *)malloc(sizeof(struct el));
			punt->next->prev=punt;
			punt = punt->next;
			printf("\nInserisci il %d elemento:\n", i);
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


struct el* conc_liste(struct el* l1, struct el* l2){
	struct el* l;
	if(l1!=NULL && l2!=NULL){
		
		l2->next=conc_liste(l1,l2->next);
		
		if(l2->next == NULL){
			l2->next = l1;
			l1->prev = l2;
		}	
		
	}
	return l2;
	
}


