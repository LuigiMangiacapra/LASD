/*
Creare una lista e sostituire tutti gli elementi che hanno come elementi precedenti 
una somma pari con la somma + 1 di quest'ultimi
	esempio:
		input: 1 2 3 4 5 6
		output: 1 2 3 7 11 6  (perché 1+2+3 è pari e 1+2+3+4 è pari)
*/

#include <stdio.h>
#include <stdlib.h>
#include <malloc.h>

#define MAX 20

struct elem *crea_lista(int n);
void visualizza_lista(struct elem *lista);
struct elem* somma_pari_in_next(struct elem *lista, int pos, int somma, int num_values);


struct elem{
	int inf;
	struct elem *next;
};


int main(){
	int pos = 0, somma = 0;
	struct elem* elem = NULL;
	struct elem *lista = NULL; //puntatore che si collega alla struct per creare la lista
	int n;
	printf("Specificare numero di elementi\n");
	scanf("%d", &n);
	lista=crea_lista(n);
	lista = somma_pari_in_next(lista, pos, somma, n);
	visualizza_lista(lista);
}


struct elem *crea_lista(int n){
	struct elem *testa, *punt;
	int i;
	
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


int is_prime(int n){
	int m, i = 0, flag = 0;
	m=n/2;    
	for(i=2;i<=m;i++){    
		if(n%i==0){      
			flag=1;    
			break;    
		}    
	}    
	if(flag==0)    
		return 1;    
	return 0;  
}


int find_somma(struct elem* lista, int somma){
	
	if(lista != NULL){
		
		somma = find_somma(lista->next, somma);
		if(is_prime(lista->inf)){
			somma = somma + lista->inf;
		}
	}
	return somma;
}


struct elem* somma_pari_in_next(struct elem *lista, int pos, int somma, int num_values){
	struct elem* temp = NULL;
	if(lista != NULL){
		
		somma = somma + lista->inf;
		
		lista->next = somma_pari_in_next(lista->next, pos, somma, num_values);
		
		if(somma % 2 == 0){
			printf("somma: %d\n", somma);
			temp = lista;
			lista = lista->next;
			lista->inf = somma + 1;
			lista = temp;
		}
	}
	return lista;
}
